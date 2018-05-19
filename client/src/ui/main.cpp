/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "yaml.h"
#include "girder_short.h"
#include "girder_long.h"
#include "camera.h"
#include "worm.h"
#include "map_game.h"
#include "window_game.h"


int main( int argc, char* args[] ) {
	//Start up SDL and create window
	View::WindowGame window;
	SDL_Renderer * renderer = window.getRenderer();
	YAML::Node nodeModel = YAML::LoadFile("../modelo.yml");
	View::MapGame myMapGame(renderer, nodeModel);

	//std::cout << "Resolution " << this->screen_width << "x" << this->screen_height << std::endl;

	View::GirderShort myGirder(renderer);
	//View::GirderLong mouseGirder(renderer);
	View::Texture background;
	background.loadFromFile("../../resources/graphics/fondo_grande.jpg", renderer);

				//Main loop flag
	bool quit = false;
	//int xMouse, yMouse;
	//SDL_GetMouseState(&xMouse, &yMouse);
					
	//Event handler
	SDL_Event e;
	View::Worm myWorm(renderer);
	View::Worm myWorm2(renderer);
	View::GirderShort myShortGirder(renderer);
	View::Camera camera(window.getWidth(), window.getHeight(), background.getWidth(), background.getHeight());

	myShortGirder.setX(600);
	myShortGirder.setY(420);
	myWorm.setX(600);
	myWorm.setY(400);
	myWorm2.setX(100);
	myWorm2.setY(100);
	
		//While application is running
		while( !quit ) {
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 ) {
				//User requests quit
				if(e.type == SDL_QUIT) {
					quit = true;
				}
				if (e.type == SDL_KEYDOWN) {
					if (e.key.keysym.sym == SDLK_LEFT) {
						camera.setX(camera.getX()-10);
					}
					if (e.key.keysym.sym == SDLK_RIGHT) {
						camera.setX(camera.getX()+10);
					}						if (e.key.keysym.sym == SDLK_UP) {
						camera.setY(camera.getY()-10);
					}
					if (e.key.keysym.sym == SDLK_DOWN) {
						camera.setY(camera.getY()+10);
					}
				}
			}

				//Clear screen
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
				SDL_RenderClear(renderer);

				SDL_Rect cam = camera.getCamera();

				// Dibujo el fondo
				background.render(renderer, 0, 0, &cam);
				
        myShortGirder.render(renderer, camera.getX(), camera.getY());
				myWorm.render(renderer, camera.getX(), camera.getY());
				//camera.focus(myShortGirder);
				
				myWorm2.render(renderer, camera.getX(), camera.getY());        

				//Update screen
				SDL_RenderPresent(renderer);
		}
	return 0;
}