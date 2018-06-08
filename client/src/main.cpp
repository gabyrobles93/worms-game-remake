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
#include "sdl_timer.h"
#include "client_configuration.h"

#define CONNECTION_HOST "localhost"
#define CONNECTION_PORT "8080"
#define MAX_QUEUE_MODELS 256
#define TEAM_ID 1

#define CLOCK_X_OFFSET 10
#define CLOCK_Y_OFFSET 10
#define CLOCK_WIDTH 120
#define CLOCK_HEIGHT 120

#define CONSTANT_WAIT 100/6

#define HARCODED_POWER_SHOOT 1

// Variable global
Paths gPath;

int main(/* int argc, char *argv[] */) try {
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
	View::WindowGame mainWindow(staticMap, 800, 600);
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

	int timeLostSleeping = 0;
	int ti; 
	int tf;
	int updateCount = 0;
	int renderCount = 0;

	ClientConfiguration cfg;

	while (!quit) {
		ti = SDL_GetTicks();
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				quit = true;
			
			cfg.handleEvent(e);

			if (cfg.hasShooted()) {
				Event event(a_shoot, inventory.getSelectedWeapon(), TEAM_ID, cfg.getWeaponsCountdown(), cfg.getPowerShoot());
				events.push(event);
			}

			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_w) {
					Event event(a_pointUp, TEAM_ID);
					events.push(event);
				}
				if (e.key.keysym.sym == SDLK_s) {
					Event event(a_pointDown, TEAM_ID);
					events.push(event);
				}
				if (e.key.keysym.sym == SDLK_a) {
					Event event(a_moveLeft, TEAM_ID);
					events.push(event);
				}
				if (e.key.keysym.sym == SDLK_d) {
					Event event(a_moveRight, TEAM_ID);
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

				if (e.key.keysym.sym == SDLK_LEFT) {
					camera.handleEvent(e);
				}
				if (e.key.keysym.sym == SDLK_RIGHT) {
					camera.handleEvent(e);
				}
				if (e.key.keysym.sym == SDLK_UP) {
					camera.handleEvent(e);
				}
				if (e.key.keysym.sym == SDLK_DOWN) {
					camera.handleEvent(e);
				}
			}

			inventory.handleEvent(e); 
		}

		camera.updateCameraPosition();

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		
		// Dibujamos cosas estáticas
		mainWindow.render(camera);

		// Procesamiento de los snapshoots
		bool thereIsModel = pdynamics.popModel();
		while (thereIsModel) {
			updateCount++;
			/* std::cout << "Pop & Updating \n"; */
			worms.update(pdynamics.getWorms());
			worms.updateWormProtagonic(pdynamics.getWormProtagonicId());
			projectiles.update(renderer, pdynamics.getProjectiles());
			clock.setTime(pdynamics.getTurnTimeLeft());
			thereIsModel = pdynamics.popModel();
		}
		renderCount++;
		/* std::cout << "Rendering \n"; */
		// Dibujamos cosas dinámicas
		// Gusanos
		worms.render(renderer, camera);

		// Proyectiles
		projectiles.render(renderer, camera);

		// El agua va sobre todo menos el inventario
		mainWindow.renderWater(camera);

		// El inventario y el timer va adelante de todo
		inventory.render(renderer);

		// Dibujamos los objetos configurables por el cliente
		cfg.render(renderer);
		
		clock.render(renderer, 0, 0);

		SDL_RenderPresent(renderer);
		tf = SDL_GetTicks();
		//std::cout << "tf " << tf << " ti " << ti << " pilin " << pilin << std::endl;

		int to_sleep = CONSTANT_WAIT - (tf-ti) - timeLostSleeping;
		if (to_sleep < 0) {
			timeLostSleeping = 0;
		} else {
			SDL_Delay(to_sleep);
			timeLostSleeping = SDL_GetTicks() - (tf - to_sleep);
		}
	
	}

	// Salimos del ciclo del juego, enviamos evento de que nos fuimos.
	Event event(a_quitGame, TEAM_ID);
	events.push(event);

	// Stop y Join de threads
	event_sender.stop();
	event_sender.join();
	model_receiver.stop();
	model_receiver.join();

	std::cout << "Se termino el programa con" << std::endl;
	std::cout << "Renders count " << renderCount << std::endl;
	std::cout << "Updates count " << updateCount << std::endl;
	
	return 0;
	
} catch(const SocketError & e) {
	std::cout << e.what() << std::endl;
} catch(const std::exception & e) {
		std::cout << e.what() << std::endl;
}
