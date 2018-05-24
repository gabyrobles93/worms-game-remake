#include <iostream>
#include <fstream>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "yaml.h"
#include "camera.h"
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
#include "protected_dynamics.h"
#include "event.h"

#define CONNECTION_HOST "localhost"
#define CONNECTION_PORT "8080"
#define MAX_QUEUE_MODELS 256
#define TEAM_ID 1

int main(/* int argc, char *argv[] */)
try {
    YAML::Node mapNode;
    Queue<Event> events(MAX_QUEUE_MODELS);
    Protocol protocol(SocketConnection(CONNECTION_HOST, CONNECTION_PORT));
    EventSender event_sender(protocol, events);
    protocol.rcvGameMap(mapNode);

	YAML::Node staticMap = mapNode["static"];
	YAML::Node dynamicMap = mapNode["dynamic"];
	YAML::Node wormsNode = dynamicMap["worms"];

	ProtectedDynamics pdynamics(dynamicMap);
	ModelReceiver model_receiver(protocol, pdynamics);

    // Creo la pantalla con dichas cosas estáticas.
	View::WindowGame mainWindow(staticMap);
	SDL_Renderer * renderer = mainWindow.getRenderer();
	View::Camera camera(mainWindow.getScreenWidth(), mainWindow.getScreenHeight(),
						mainWindow.getBgWidth(), mainWindow.getBgHeight());

	View::WormsStatus worms(wormsNode, renderer);
	View::Inventory inventory(renderer);
    // Lanzo threads de enviar eventos y de recibir modelos
    event_sender.start();
    model_receiver.start();

	// Comienza el ciclo del juego para el cliente
	bool quit = false;	
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				quit = true;
			
            // Chequeo eventos de teclado (ver si se puede hacer mas prolijo)
            // FALTA CHEQUEAR EVENTOS DE MOUSE (CLICKS, MOVIMIENTOS DE CAMARA, ETC)
			if (e.type == SDL_KEYDOWN) {
				camera.handleEvent(e);
				
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
					Event event(a_shoot, TEAM_ID);
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
				if (e.key.keysym.sym == SDLK_1) {
					Event event(a_choose1SecDeton, TEAM_ID);
					events.push(event);
				}
				if (e.key.keysym.sym == SDLK_2) {
					Event event(a_choose2SecDeton, TEAM_ID);
					events.push(event);
				}
				if (e.key.keysym.sym == SDLK_3) {
					Event event(a_choose3SecDeton, TEAM_ID);
					events.push(event);
				}
				if (e.key.keysym.sym == SDLK_4) {
					Event event(a_choose4SecDeton, TEAM_ID);
					events.push(event);
				}
				if (e.key.keysym.sym == SDLK_5) {
					Event event(a_choose5SecDeton, TEAM_ID);
					events.push(event);
				}
				if (e.key.keysym.sym == SDLK_TAB) {
					Event event(a_changeWorm, TEAM_ID);
					events.push(event);
				}
				// Si es Q y el inventario esta abierto
				// elige el arma siguiente
				if (e.key.keysym.sym == SDLK_q) {
					if (inventory.isOpen()) {
						inventory.pickNextWeapon();
					}
				}           
			}

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_RIGHT) {
					inventory.toggleOpen();
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		
    // Dibujamos cosas estáticas
		mainWindow.render(camera);

		// Dibujamos cosas dinámicas
		worms.update(pdynamics.getWorms());
		worms.render(renderer, camera);

		// El agua va sobre todo menos el inventario
		mainWindow.renderWater(camera);

		// El inventario va adelante de todo
		inventory.render(renderer, 10, 10);

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
