#include "window_game.h"
#include "yaml.h"
#include "map_game.h"
#include "worm.h"
#include "camera.h"

View::WindowGame::WindowGame(int w, int h) {
    this->screen_width = w;
    this->screen_height = h;

    this->init();
}

View::WindowGame::~WindowGame() {
    this->close();
}

int View::WindowGame::getWidthResolution(void) {
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	return DM.w;
}

int View::WindowGame::getHeightResolution(void) {
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	return DM.h;
}

void View::WindowGame::init(void) {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw View::Exception("%s. SDL Error: %s", ERR_MSG_SDL_INIT_VIDEO, SDL_GetError());
	} else {
		// Set texture filtering to linear
		if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		
		// Si se inicio con los argumentos en 0 se inicializa con 
		// el tamano de la pantalla
		if (!this->screen_width && !this->screen_height) {
			this->screen_width = this->getWidthResolution();
			this->screen_height = this->getHeightResolution();
		}

		// Create window
		this->window = SDL_CreateWindow(
            "Worms Taller Party", 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            this->screen_width, 
            this->screen_height, 
            SDL_WINDOW_FULLSCREEN
        );

		if (this->window == NULL) {
            throw View::Exception("%s. SDL Error: %s", ERR_MSG_SDL_CREATE_WINDOW, SDL_GetError());
		} else {
			//Create this->renderer for window
			//this->renderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (this->renderer == NULL) {
                throw View::Exception("%s. SDL Error: %s", ERR_MSG_SDL_CREATE_RENDERER, SDL_GetError());
			} else {
				//Initialize this->renderer color
				SDL_SetRenderDrawColor( this->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
                    throw View::Exception("%s. SDL Error: %s", ERR_MSG_SDL_IMAGE_INIT, IMG_GetError());
				}
			}
		}
	}
}

void View::WindowGame::close(void) {
	//Destroy window	
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	this->window = NULL;
	this->renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer * View::WindowGame::getRenderer(void) const {
	return this->renderer;
}

int View::WindowGame::getWidth(void) const {
	return this->screen_width;
}

int View::WindowGame::getHeight(void) const {
	return this->screen_height;
}