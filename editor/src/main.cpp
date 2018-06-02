#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "window_game.h"
#include "girder_long.h"
#include "paths.h"
#include "girder_short.h"
#include "inventory.h"
#include "inventory_editor.h"
#include "inventory_weapons.h"
#include "map_game.h"
#include "worm.h"
#include "yaml.h"

#define ARGC_DEFAULT 1
#define ARGC_FILE_CONFIG 2

// Variable global
Paths gPath;

void validateArgs(int, char*[], YAML::Node & map);

int main(int argc, char * argv[]) {
	YAML::Node map;
	validateArgs(argc, argv, map);

	int teamsAmount = map["static"]["teams_amount"].as<int>();
	int wormsHealth = map["static"]["worms_health"].as<int>();

	// Creamos el objeto map game con el nodo ya inicializado
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

void validateArgs(int argc, char * argv[], YAML::Node & map) {
	// Parametros por default
	if (argc == ARGC_DEFAULT) {
		std::cout << "Default configuration" << std::endl;
		YAML::Node initInventory;
		YAML::Node bazooka;
		YAML::Node grenade;
		std::string path = "../../resources/graphics/lava_pattern.jpg";
		std::string display = "expanded";
		int waterLevel = 300;
		int teamsAmount = 3;
		int wormsHealth = 100;
		bazooka["item_name"] = WEAPON_NAME_BAZOOKA;
		bazooka["supplies"] = INFINITY_SUPPLIES;
		grenade["item_name"] = WEAPON_NAME_GREEN_GRENADE;
		grenade["supplies"] = 5;
		initInventory["init_inventory"].push_back(bazooka);
		initInventory["init_inventory"].push_back(grenade);

		// Creamos el nodo principal del mapa
		// y el objeto MapGame
		map["static"]["background"]["file"] = path;
		map["static"]["background"]["display"] = display;
		map["static"]["water_level"] = waterLevel;
		map["static"]["init_inventory"] = initInventory["init_inventory"];
		map["static"]["teams_amount"] = teamsAmount;
		map["static"]["worms_health"] = wormsHealth;
	}

	if (argc == ARGC_FILE_CONFIG) {
		try {
			map = YAML::LoadFile(argv[ARGC_FILE_CONFIG - 1]);
		} catch (std::exception e) {
			std::cerr << "La primer ruta no funciono" << std::endl;
			std::cerr << "El path era " << argv[ARGC_FILE_CONFIG - 1] << std::endl;
			map = YAML::LoadFile(argv[ARGC_FILE_CONFIG - 1]);
		}		
	}
}
