#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "yaml.h"
#include "girder_short.h"
#include "girder_long.h"
#include "map_game.h"
#include "window_game.h"
#include "camera.h"


int main() {
	//Start up SDL and create window
	YAML::Node mapNode = YAML::LoadFile("../map.yml");
	View::WindowGame mainWindow(mapNode);

	SDL_Renderer * renderer = mainWindow.getRenderer();
	View::Camera camera(mainWindow.getScreenWidth(), mainWindow.getScreenHeight(),
						mainWindow.getBgWidth(), mainWindow.getBgHeight());

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				quit = true;
			
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_LEFT) {
					camera.setX(camera.getX()-10);
				}
				if (e.key.keysym.sym == SDLK_RIGHT) {
					camera.setX(camera.getX()+10);
				}
				if (e.key.keysym.sym == SDLK_UP) {
					camera.setY(camera.getY()-10);
				}
				if (e.key.keysym.sym == SDLK_DOWN) {
					camera.setY(camera.getY()+10);
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		mainWindow.render(camera);
		SDL_RenderPresent(renderer);
	}	

	return 0;
}