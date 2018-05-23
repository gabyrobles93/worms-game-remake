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

#define CONNECTION_HOST "localhost"
#define CONNECTION_PORT "8080"

int main(/* int argc, char *argv[] */)
try {
    YAML::Node mapNode;
    BlockingQueue<action_t> events;
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
				if (e.key.keysym.sym == SDLK_a) {
					camera.setX(camera.getX()-100);
				}
				if (e.key.keysym.sym == SDLK_d) {
					camera.setX(camera.getX()+100);
				}
				if (e.key.keysym.sym == SDLK_w) {
					camera.setY(camera.getY()-100);
				}
				if (e.key.keysym.sym == SDLK_s) {
					camera.setY(camera.getY()+100);
				}
				if (e.key.keysym.sym == SDLK_UP) {
					events.push(a_pointUp);
				}
				if (e.key.keysym.sym == SDLK_DOWN) {
					events.push(a_pointDown);
				}
				if (e.key.keysym.sym == SDLK_LEFT) {
					events.push(a_moveLeft);
				}
				if (e.key.keysym.sym == SDLK_RIGHT) {
					events.push(a_moveRight);
				}
				if (e.key.keysym.sym == SDLK_SPACE) {
					events.push(a_shoot);
				}
				if (e.key.keysym.sym == SDLK_RETURN) {
					events.push(a_frontJump);
				}
				if (e.key.keysym.sym == SDLK_BACKSPACE) {
					events.push(a_backJump);
				}
				if (e.key.keysym.sym == SDLK_1) {
					events.push(a_choose1SecDeton);
				}
				if (e.key.keysym.sym == SDLK_2) {
					events.push(a_choose2SecDeton);
				}
				if (e.key.keysym.sym == SDLK_3) {
					events.push(a_choose3SecDeton);
				}
				if (e.key.keysym.sym == SDLK_4) {
					events.push(a_choose4SecDeton);
				}
				if (e.key.keysym.sym == SDLK_5) {
					events.push(a_choose5SecDeton);
				}

				// Si es TAB y el inventario esta abierto
				// elige el arma siguiente
				if (e.key.keysym.sym == SDLK_TAB) {
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
		inventory.render(renderer, 10, 10);

		// Dibujamos cosas dinámicas
		worms.update(pdynamics.getWorms());
		worms.render(renderer, camera);
		
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}

	// Salimos del ciclo del juego, enviamos evento de que nos fuimos.
	events.push(a_quitGame);

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
