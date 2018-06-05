#include <iostream>
#include <fstream>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "yaml.h"
#include "camera.h"
#include "clock.h"
#include "socket.h"
#include "socket_error.h"
#include "protocol.h"
#include "protocol_error.h"
#include "thread.h"
#include "blocking_queue.h"
#include "yaml.h"
#include "event_sender.h"
#include "model_receiver.h"
#include "window_game.h"
#include "camera.h"
#include "types.h"
#include "worms_status.h"
#include "inventory.h"
#include "inventory_weapons.h"
#include "protected_dynamics.h"
#include "event.h"
#include "paths.h"
#include "projectiles.h"
#include "dynamite.h"
#include "explosion.h"

#define CONNECTION_HOST "localhost"
#define CONNECTION_PORT "8080"
#define MAX_QUEUE_MODELS 256
#define TEAM_ID 1

#define CLOCK_X_OFFSET 10
#define CLOCK_Y_OFFSET 10
#define CLOCK_WIDTH 120
#define CLOCK_HEIGHT 120

// Variable global
Paths gPath;

int main(/* int argc, char *argv[] */) {


	// No se puede borrar nodo de una sequence en yaml
	// issue: https://github.com/jbeder/yaml-cpp/issues/190
	/* 
	YAML::Node ejemplo;
	YAML::Node seq1;
	seq1["id"] = 1;
	seq1["type"] = "Dynamite";

	YAML::Node seq2;
	seq2["id"] = 2;
	seq2["type"] = "Bazooka";

	YAML::Node seq3;
	seq3["id"] = 3;
	seq3["type"] = "Banana";

	ejemplo["projectiles"].push_back(seq1);
	ejemplo["projectiles"].push_back(seq2);
	ejemplo["projectiles"].push_back(seq3);

	std::cout << "Nodo antes de borrar\n";
	std::cout << ejemplo << std::endl;

	YAML::iterator it = ejemplo["projectiles"].begin();

	int index = 0;
	for (; it != ejemplo["projectiles"].end() ; it++) {
		YAML::Node current = *it;
		if ((*it)["id"].as<int>() == 2) {
			std::cout << "Removing\n";
			ejemplo["projectiles"].remove_at(index);
			break;
		}
		index++;
	}

	std::cout << "\n\n\nNodo despues de borrar\n";
	std::cout << ejemplo << std::endl;*/

	try {
		YAML::Node mapNode;
		Queue<Event> events(MAX_QUEUE_MODELS);
		Protocol protocol(SocketConnection(CONNECTION_HOST, CONNECTION_PORT));
		EventSender event_sender(protocol, events);
		protocol.rcvGameMap(mapNode);

		YAML::Node staticMap = mapNode["static"];
		YAML::Node dynamicMap = mapNode["dynamic"];
		YAML::Node wormsNode = dynamicMap["worms_teams"];

		ProtectedDynamics pdynamics(dynamicMap);
		ModelReceiver model_receiver(protocol, pdynamics);

			// Creo la pantalla con dichas cosas estáticas.
		View::WindowGame mainWindow(staticMap, 1280, 900);
		SDL_Renderer * renderer = mainWindow.getRenderer();
		View::Camera camera(mainWindow.getScreenWidth(), mainWindow.getScreenHeight(),
							mainWindow.getBgWidth(), mainWindow.getBgHeight());

		View::WormsStatus worms(wormsNode, renderer);
		View::WeaponsInventory inventory(renderer);

		View::Projectiles projectiles;
		// Lanzo threads de enviar eventos y de recibir modelos
		event_sender.start();
		model_receiver.start();

		View::Clock clock(CLOCK_X_OFFSET, mainWindow.getScreenHeight() - CLOCK_Y_OFFSET - CLOCK_HEIGHT, CLOCK_WIDTH, CLOCK_HEIGHT);
		// Comienza el ciclo del juego para el cliente
		bool quit = false;	
		SDL_Event e;

		while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT)
					quit = true;
				
				if (e.type == SDL_KEYDOWN) {
					if (e.key.keysym.sym == SDLK_UP) {
						Event event(a_pointUp, TEAM_ID);
						events.push(event);
					}
					if (e.key.keysym.sym == SDLK_DOWN) {
						Event event(a_pointDown, TEAM_ID);
						events.push(event);
					}
					if (e.key.keysym.sym == SDLK_LEFT) {
						Event event(a_moveLeft, TEAM_ID);
						events.push(event);
					}
					if (e.key.keysym.sym == SDLK_RIGHT) {
						Event event(a_moveRight, TEAM_ID);
						events.push(event);
					}
					if (e.key.keysym.sym == SDLK_SPACE) {
						Event event(a_shoot, inventory.getSelectedWeapon(), TEAM_ID);
						events.push(event);
					}
					if (e.key.keysym.sym == SDLK_RETURN) {
						Event event(a_frontJump, TEAM_ID);
						events.push(event);
					}
					if (e.key.keysym.sym == SDLK_BACKSPACE) {
						Event event(a_backJump, TEAM_ID);
						events.push(event);
					}
				}

				inventory.handleEvent(e); 
			}

			camera.updateCameraPosition();

			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(renderer);
			
			// Dibujamos cosas estáticas
			mainWindow.render(camera);

			// Dibujamos cosas dinámicas
			// Gusanos
			worms.update(pdynamics.getWorms());
			worms.render(renderer, camera);

			// Proyectiles
 			projectiles.update(renderer, pdynamics.getProjectiles());
			projectiles.render(renderer, camera);

			// El agua va sobre todo menos el inventario
			mainWindow.renderWater(camera);

			// El inventario y el timer va adelante de todo
			inventory.render(renderer);
			clock.setTime(pdynamics.getTurnTimeLeft());
			clock.render(renderer, 0, 0);

			SDL_RenderPresent(renderer);
			SDL_Delay(10);
		}

		// Salimos del ciclo del juego, enviamos evento de que nos fuimos.
		Event event(a_quitGame, TEAM_ID);
		events.push(event);

		// Stop y Join de threads
		event_sender.stop();
		event_sender.join();
		model_receiver.stop();
		model_receiver.join();

		return 0;

	} catch(const SocketError & e) {
		std::cout << e.what() << std::endl;
	} catch(const std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}

