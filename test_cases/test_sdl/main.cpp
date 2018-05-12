/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "girder_short.h"
#include "girder_long.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

// Vector de vigas creadas
std::vector<View::GirderLong*> longGirders;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	return success;
}

void close() {
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	for (size_t i = 0 ; i < longGirders.size() ; i++) {
		delete longGirders[i];
	}

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//View::GirderShort myGirder(gRenderer);
			View::GirderLong mouseGirder(gRenderer);
            //Main loop flag
			bool quit = false;
			int xMouse, yMouse;
			SDL_GetMouseState(&xMouse, &yMouse);
            
			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 ) {
					//User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					}

					if (e.type == SDL_MOUSEMOTION) {
						SDL_GetMouseState(&xMouse, &yMouse);
					}

					if (e.type == SDL_MOUSEWHEEL) {
						// Scroll up
						if (e.wheel.y > 0) {
							mouseGirder.rotateClockwise();
						}
						// Scroll down
						if (e.wheel.y < 0) {
							mouseGirder.rotateCounterClockwise();
						}
					}

					if (e.type == SDL_MOUSEBUTTONDOWN) {
						longGirders.push_back(new View::GirderLong(gRenderer, mouseGirder.getCurrentDegrees()));
						(*longGirders.back()).render(gRenderer, xMouse - mouseGirder.getWidth() / 2, yMouse - mouseGirder.getHeight() / 2);
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render background texture to screen
				//myGirder.render(gRenderer, 0, 0 );

				for (size_t i = 0 ; i < longGirders.size() ; i++) {
					View::GirderLong & current = *longGirders.at(i);
					current.render(gRenderer, current.getX(), current.getY());
				}

				mouseGirder.render(gRenderer, xMouse - mouseGirder.getWidth() / 2, yMouse - mouseGirder.getHeight() / 2);
                

				//Update screen
				SDL_RenderPresent( gRenderer );
				//myGirder.rotateClockwise();
				//SDL_Delay(100);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}