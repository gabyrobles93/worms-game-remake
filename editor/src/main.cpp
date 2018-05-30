#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "window_game.h"
#include "girder_long.h"
#include "girder_short.h"
#include "inventory_editor.h"
#include "map_game.h"
#include "worm.h"
#include "yaml.h"

#define MAX_ARG 4
#define POS_BG_PATH 1
#define POS_BG_DISP 2
#define POS_WATER_LEVEL 3


int validateArgs(int, char*[]);

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
	
	// Creamos el nodo principal del mapa
	// y el objeto MapGame
	YAML::Node map;
	map["static"]["background"]["file"] = path;
	map["static"]["background"]["display"] = display;
	map["static"]["water_level"] = waterLevel;
	View::MapGame mapGame(map);

	// Creamos la ventana con la parte estatica (vacia)
	YAML::Node staticMap = map["static"];
	View::WindowGame editorWindow(staticMap);

	// Renderer del programa
	SDL_Renderer * renderer = editorWindow.getRenderer();

	// Inicializamos la camara
	View::Camera camera(
		editorWindow.getScreenWidth(), 
		editorWindow.getScreenHeight(),
		editorWindow.getBgWidth(), 
		editorWindow.getBgHeight()
	);

	// Creamos el inventario y lo abrimos
	View::EditorInventory editorInventory(renderer, teamsAmount, wormsHealth);
	editorInventory.toggleOpen();

	bool quit = false;
	bool validMap;
	SDL_Event e;
	while (!quit) {
		int camX = camera.getX(), camY = camera.getY();
		
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				editorWindow.hide();
				validMap = mapGame.hasAllTheWorms(teamsAmount, AMOUNT_WORMS_PER_TEAM);
				if (!validMap) {
					std::cout << "Para poder guardar el mapa debe dibujar todos los gusanos disponibles" << std::endl;
					std::string ans;
					std::cout << "Desea continuar editando el mapa? [y/n]" << std::endl;
					while (std::cin >> ans) {
						if (ans == "n" || ans == "y") {
							break;
						}
						std::cout << "Desea continuar editando el mapa? [y/n]" << std::endl;
					}

					if (ans == "y") {
						editorWindow.show();
						quit = false;
					}
				}
			}

			if (e.type == SDL_KEYDOWN) {
				
					if (e.key.keysym.sym == SDLK_z && (e.key.keysym.mod & KMOD_CTRL)) {
						mapGame.setPreviousState(editorInventory);
					}
					
					if (e.key.keysym.sym == SDLK_y && (e.key.keysym.mod & KMOD_CTRL)) {
						mapGame.setNextState(editorInventory);
					}
				
			}

			editorInventory.handleEvent(renderer, e, mapGame, camX, camY);
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		camera.updateCameraPosition();

		editorWindow.render(camera);

		mapGame.render(renderer, camX, camY);
		
		editorInventory.renderSelectedInMouse(renderer);

		editorWindow.renderWater(camera);

		editorInventory.render(renderer);
		
		SDL_RenderPresent(renderer);
		SDL_Delay(10); // Para no usar al mango el CPU
	}

	if (validMap) {
		std::string ans;
		std::cout << "Desea guardar el mapa? [y/n]" << std::endl;
		while (std::cin >> ans) {
			if (ans == "n" || ans == "y") {
				break;
			}
			std::cout << "Desea guardar el mapa? [y/n]" << std::endl;
		}			
		
		if (ans == "y") {
			std::cout << "Ingrese el nombre del mapa" << std::endl;
			std::cin >> ans;

			mapGame.saveAs(ans);
		}
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
