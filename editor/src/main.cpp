#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "window_game.h"
#include "girder_long.h"
#include "girder_short.h"
#include "inventory_editor.h"
#include "worm.h"
#include "yaml.h"

#define MAX_ARG 4
#define POS_BG_PATH 1
#define POS_BG_DISP 2
#define POS_WATER_LEVEL 3

int validateArgs(int, char*[]);

// Dibuja lo que ya fue clickeado por el usuario
void renderObjectsPlaced(
	SDL_Renderer * r,
	std::vector<View::GirderShort*>  & shortCollection,
	std::vector<View::GirderLong*> & longCollection,
	std::map<std::size_t, std::vector<View::Worm*>> & wormsCollection,
	int camX,
	int camY
);

int main(int argc, char * argv[]) {

	//validateArgs(argc, argv);

	// Parametros configurables por el usuario
	// a la derecha las configuraciones
	std::string path; // Archivo valido
	std::string display; // centered | expanded | mosaic
	int waterLevel; // Todavia no defini un maximo de nivel del agua pero sera 0 < waterlevel < MAX_WATER_LEVEL
	int teamsAmount; // 2 o mas team
	int wormsHealth; // 1 < wormsHealth < 100

	if (argc == 1) {
		// Parametros por default
		std::cout << "Default configuration" << std::endl;
		path = "../../resources/graphics/lava_pattern.jpg";
		display = "expanded";
		waterLevel = 300;
		teamsAmount = 3;
		wormsHealth = 100;
	}
	
	YAML::Node map;
	map["static"]["background"]["file"] = path;
	map["static"]["background"]["display"] = display;
	map["static"]["water_level"] = waterLevel;
	/*map["static"]["short_girders"];
	map["static"]["long_girders"];
	map["dynamic"]["worms"];*/

	/* Luego hay que cargarle secuencias de nodos.
	YAML::Node girderNode1;
	girderNode1["id"] = 1;
	girderNode1["x"] = 100;
	girderNode1["y"] = 200;
	YAML::Node girderNode2;
	girderNode2["id"] = 2;
	girderNode2["x"] = 10;
	girderNode2["y"] = 20;
	map["static"]["long_girders"].push_back(girderNode1);
	map["static"]["long_girders"].push_back(girderNode2);
	*/

	YAML::Node staticMap = map["static"];

	View::WindowGame editorWindow(staticMap);
	SDL_Renderer * renderer = editorWindow.getRenderer();
	View::Camera camera(
		editorWindow.getScreenWidth(), 
		editorWindow.getScreenHeight(),
		editorWindow.getBgWidth(), 
		editorWindow.getBgHeight()
	);

	View::EditorInventory editorInventory(renderer, teamsAmount, wormsHealth);
	editorInventory.toggleOpen();

	// Estructuras donde se guardan lo que se va dibujando.
	// Al final del programa se libera la memomria y se 
	// pasa esta data a un archvio YAML
	std::vector<View::GirderShort*> shortCollection;
	std::vector<View::GirderLong*> longCollection;
	std::map<std::size_t, std::vector<View::Worm*>> wormsCollection;

	// Comienza el ciclo del juego para el cliente
	bool quit = false;	
	SDL_Event e;
	while (!quit) {
		int camX = camera.getX(), camY = camera.getY();
		
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			editorInventory.handleEvent(renderer, e, shortCollection, longCollection, wormsCollection, camX, camY);
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		camera.updateCameraPosition();

		editorWindow.render(camera);

		renderObjectsPlaced(renderer, shortCollection, longCollection, wormsCollection, camX, camY);
		
		editorInventory.renderSelectedInMouse(renderer);

		editorWindow.renderWater(camera);

		editorInventory.render(renderer, 10, 10);
		
		SDL_RenderPresent(renderer);
		SDL_Delay(10); // Para no usar al mango el CPU
	}
				


	return 0;
}

int validateArgs(int argc, char * argv[]) {
	int error = 0;
	if (argc != MAX_ARG) {
		error = 1;
	}

	if (error) {
		std::cerr << "La invocacion del programa es: " << std::endl;
		std::cerr << "./editor <path to background file> <background display mode> <water level>\n";
		std::cerr << "display mode disponibles: mosaic | centered | expanded \n";
	}
	return 0;
}

void renderObjectsPlaced(
	SDL_Renderer * renderer,
	std::vector<View::GirderShort*>  & shortCollection,
	std::vector<View::GirderLong*> & longCollection,
	std::map<std::size_t, std::vector<View::Worm*>> & wormsCollection,
	int camX,
	int camY
) {

	for (size_t i = 0 ; i < shortCollection.size() ; i++) {
		shortCollection.at(i)->render(renderer, camX, camY);
	}

	for (size_t i = 0 ; i < longCollection.size() ; i++) {
		longCollection.at(i)->render(renderer, camX, camY);
	}

	std::map<std::size_t, std::vector<View::Worm*>>::iterator itMap = wormsCollection.begin();
	for (; itMap != wormsCollection.end() ; itMap++) {
		std::vector<View::Worm*>::iterator it = itMap->second.begin();
		for (; it != itMap->second.end() ; it++) {
			(*it)->render(renderer, camX, camY);
		}
	}
}