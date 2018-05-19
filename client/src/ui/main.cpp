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


int main( int argc, char* args[] ) {
	//Start up SDL and create window

YAML::Node nodeModel = YAML::LoadFile("../modelo.yml");
		View::MapGame myMapGame(this->renderer, nodeModel);

		std::cout << "Resolution " << this->screen_width << "x" << this->screen_height << std::endl;

		View::GirderShort myGirder(this->renderer);
		//View::GirderLong mouseGirder(this->renderer);
		View::Texture background;
		background.loadFromFile("../images/fondo_grande.jpg", this->renderer);

         //Main loop flag
		bool quit = false;
		//int xMouse, yMouse;
		//SDL_GetMouseState(&xMouse, &yMouse);
            
		//Event handler
		SDL_Event e;
		View::Worm myWorm(this->renderer);
		View::Worm myWorm2(this->renderer);
		View::GirderShort myShortGirder(this->renderer);
		View::Camera camera(getWidthResolution(), getHeightResolution(), background.getWidth(), background.getHeight());

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

				SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0x00, 0x00 );
				SDL_RenderClear( this->renderer );

				SDL_Rect cam = camera.getCamera();
				// Dibujo el fondo
				background.render(this->renderer, 0, 0, &cam);

				//Render background texture to screen
				//myGirder.render(this->renderer, 0, 0 );

				for (size_t i = 0 ; i < longGirders.size() ; i++) {
					View::GirderLong & current = *longGirders.at(i);
					current.render(this->renderer, current.getX(), current.getY());
				}

				//mouseGirder.render(this->renderer, xMouse - mouseGirder.getWidth() / 2, yMouse - mouseGirder.getHeight() / 2);
				
        myShortGirder.render(this->renderer, camera.getX(), camera.getY());
				myWorm.render(this->renderer, camera.getX(), camera.getY());
				//camera.focus(myShortGirder);
				
				myWorm2.render(this->renderer, camera.getX(), camera.getY());        

				//Update screen
				SDL_RenderPresent( this->renderer );

				//myGirder.rotateClockwise();
				//SDL_Delay(100);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}