#include <iostream>
#include <fstream>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

#define CONNECTION_HOST "localhost"
#define CONNECTION_PORT "8080"

int main(/* int argc, char *argv[] */)
try {
    YAML::Node mapNode;

    // Creo una cola bloqueante de eventos, que son action_t (Ver common/src/types.h)
    BlockingQueue<action_t> events;
    Protocol protocol(SocketConnection(CONNECTION_HOST, CONNECTION_PORT));
    EventSender event_sender(protocol, events);
    ModelReceiver model_receiver(protocol, mapNode);

    // Recibo el mapa (solo cosas estáticas) del servidor.
    protocol.rcvGameMap(mapNode);

	YAML::Node staticMap = mapNode["static"];
	YAML::Node dynamicMap = mapNode["dynamic"];

    // Creo la pantalla con dichas cosas estáticas.
	View::WindowGame mainWindow(staticMap);
	SDL_Renderer * renderer = mainWindow.getRenderer();
	View::Camera camera(mainWindow.getScreenWidth(), mainWindow.getScreenHeight(),
						mainWindow.getBgWidth(), mainWindow.getBgHeight());

	View::WormsStatus worms(dynamicMap, renderer);
	View::Inventory inventory(renderer);
    // Lanzo threads de enviar eventos y de recibir modelos
    event_sender.start();
    //model_receiver.start();

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		std::cout << "Paso a esperar un evento." << std::endl;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				quit = true;
			
            // Chequeo eventos de teclado (ver si se puede hacer mas prolijo)
            // FALTA CHEQUEAR EVENTOS DE MOUSE (CLICKS, MOVIMIENTOS DE CAMARA, ETC)
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_KP_4) {
					camera.setX(camera.getX()-100);
				}
				if (e.key.keysym.sym == SDLK_KP_6) {
					camera.setX(camera.getX()+100);
				}
				if (e.key.keysym.sym == SDLK_KP_8) {
					camera.setY(camera.getY()-100);
				}
				if (e.key.keysym.sym == SDLK_KP_2) {
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
			std::cout << "Cam X: " << camera.getX() << " Cam Y: " << camera.getY() << std::endl;
			std::cout << "Cam width: " << camera.getCamera().w << " Cam height: " << camera.getCamera().h << std::endl;
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
        // Dibujo las cosas estáticas: fondo y vigas
		mainWindow.render(camera);
		worms.render(renderer, camera);

		// Dibuja respecto de la camara
		inventory.render(renderer, 10, 10);

        // Aca habría que dibujar las cosas dinámicas que envió el servidor.
        // El hilo model_receiver recibe un nodo con cosas dinámicas para dibujar.
        // Quizá estaría bueno encapsular todo eso en un objeto, por ejemplo, llamado pepe
        // y acá hacer pepe.render(renderer, camera) para que dibuje dichas cosas dinámicas
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}

	events.push(a_quitGame);
    event_sender.stop();

    event_sender.join();
    //model_receiver.stop();
    //model_receiver.join();

	return 0;

} catch(const SocketError & e) {
    std::cout << e.what() << std::endl;
} catch(const std::exception & e) {
	std::cout << e.what() << std::endl;
}
