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

#define CONNECTION_HOST "localhost"
#define CONNECTION_PORT "8080"

int main(/* int argc, char *argv[] */)
try {
    YAML::Node mapNode;
    BlockingQueue<action_t> events;
    Protocol protocol(SocketConnection(CONNECTION_HOST, CONNECTION_PORT));
    EventSender event_sender(protocol, events);
    ModelReceiver model_receiver(protocol, mapNode);

    protocol.rcvGameMap(mapNode);

	View::WindowGame mainWindow(mapNode);
	SDL_Renderer * renderer = mainWindow.getRenderer();
	View::Camera camera(mainWindow.getScreenWidth(), mainWindow.getScreenHeight(),
						mainWindow.getBgWidth(), mainWindow.getBgHeight());

    event_sender.start();
    model_receiver.start();

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				quit = true;
			
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_KP_4) {
					camera.setX(camera.getX()-10);
				}
				if (e.key.keysym.sym == SDLK_KP_6) {
					camera.setX(camera.getX()+10);
				}
				if (e.key.keysym.sym == SDLK_KP_8) {
					camera.setY(camera.getY()-10);
				}
				if (e.key.keysym.sym == SDLK_KP_2) {
					camera.setY(camera.getY()+10);
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
			}
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		mainWindow.render(camera);
		SDL_RenderPresent(renderer);
	}

    event_sender.stop();
    event_sender.join();
    model_receiver.stop();
    model_receiver.join();

} catch(const SocketError & e) {
    std::cout << e.what() << std::endl;
}
