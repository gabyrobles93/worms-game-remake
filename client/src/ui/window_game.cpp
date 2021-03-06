#include <vector>
#include <iterator>
#include "window_game.h"
#include "yaml.h"
#include "worm.h"
#include "camera.h"
#include <limits.h>

#define MAP_WIDTH 2500
#define MAP_HEIGHT 1500
#define BACKGROUND_PATH "/usr/etc/worms/temp/background.png"

View::WindowGame::WindowGame(YAML::Node & staticNode, int w, int h, bool fs, bool ed_mode) : staticMap(staticNode) {
	this->screen_width = w;
	this->screen_height = h;
	this->full_screen = fs;
	this->edition_mode = ed_mode;
	this->init();
	if (this->edition_mode) {
		this->background.loadFromFile(this->staticMap["background"]["file"].as<std::string>(), renderer);
	} else {
		this->background.loadFromFile(BACKGROUND_PATH, renderer);
	}
	this->backgroundDisplayMode = this->staticMap["background"]["display"].as<std::string>();
	this->loadStaticObjects();
	this->water.init(
		this->renderer,
		0,
		MAP_HEIGHT - this->staticMap["water_level"].as<int>(),
		MAP_WIDTH,
		MAP_HEIGHT,
		gPath.PATH_WATER_2.c_str()
	);
}

void View::WindowGame::loadStaticObjects(void) {
	const YAML::Node & nodeShortGirders = this->staticMap["short_girders"];
	const YAML::Node & nodeLongGirders = this->staticMap["long_girders"];
	YAML::const_iterator it;

	for (it = nodeShortGirders.begin() ; it != nodeShortGirders.end() ; it++) {
		const YAML::Node & eachGirder = *it;
		View::GirderShort * newShortGirder = new View::GirderShort(this->renderer, eachGirder["angle"].as<int>());
		newShortGirder->setX(eachGirder["x"].as<int>());
		newShortGirder->setY(eachGirder["y"].as<int>());
		this->shortGirders.push_back(newShortGirder);
	}

	for (it = nodeLongGirders.begin() ; it != nodeLongGirders.end() ; it++) {
		const YAML::Node & eachGirder = *it;
		View::GirderLong * newLongGirder = new View::GirderLong(this->renderer, eachGirder["angle"].as<int>());
		newLongGirder->setX(eachGirder["x"].as<int>());
		newLongGirder->setY(eachGirder["y"].as<int>());
		this->longGirders.push_back(newLongGirder);
	}
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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw View::Exception("%s. SDL Error: %s", ERR_MSG_SDL_INIT_VIDEO, SDL_GetError());
	} else {
		// Set texture filtering to linear
		if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		
		// Si se inicio con los argumentos en 0 se inicializa con 
		// el tamano de la pantalla
		if (this->full_screen) {
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
            this->full_screen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN
        );

		if (this->window == NULL) {
			throw View::Exception("%s. SDL Error: %s", ERR_MSG_SDL_CREATE_WINDOW, SDL_GetError());
		} else {
			//Create this->renderer for window
			//this->renderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
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

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					throw View::Exception("%s. SDL Error: %s", ERR_MSG_SDL_MIXER_INIT, Mix_GetError());
				}

				// Inicializamos TTF
				if (TTF_Init() == -1) {
					throw View::Exception("%s. SDL Error: %s", ERR_MSG_SDL_TTF_INIT, TTF_GetError());
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

	//Destroy girders
	for (size_t i = 0 ; i < this->longGirders.size() ; i++) {
		delete longGirders[i];
	}

	for (size_t i = 0 ; i < this->shortGirders.size() ; i++) {
		delete shortGirders[i];
	}

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
}

SDL_Renderer * View::WindowGame::getRenderer(void) const {
	return this->renderer;
}

int View::WindowGame::getScreenWidth(void) const {
	return this->screen_width;
}

int View::WindowGame::getScreenHeight(void) const {
	return this->screen_height;
}

int View::WindowGame::getBgWidth(void) const {
	//return this->background.getWidth();
	return MAP_WIDTH;
}

int View::WindowGame::getBgHeight(void) const {
	//return this->background.getHeight();
	return MAP_HEIGHT;
}

void View::WindowGame::render(View::Camera & camera) {
	this->renderBackground(camera);

	std::vector<View::GirderLong *>::iterator it_l;
	for (it_l = this->longGirders.begin(); it_l != this->longGirders.end(); it_l++) {
		(*it_l)->render(this->renderer, camera.getX(), camera.getY());
	}

	std::vector<View::GirderShort *>::iterator it_s;
	for (it_s = this->shortGirders.begin(); it_s != this->shortGirders.end(); it_s++) {
		(*it_s)->render(this->renderer, camera.getX(), camera.getY());
	}
}

void View::WindowGame::renderWater(View::Camera & camera) {
	this->water.render(this->renderer, camera.getX(), camera.getY());
}

void View::WindowGame::renderBackground(Camera & c) {
	// Expandida
	if (this->backgroundDisplayMode == "expanded") {
		this->background.render(this->renderer, 0 - c.getX(), 0 - c.getY(), MAP_WIDTH, MAP_HEIGHT);
		return;
	}	

	// Mosaico
	int bgW = this->background.getWidth();
	int bgH = this->background.getHeight();
	if (this->backgroundDisplayMode == "mosaic") {
		for (size_t i = 0 ; i * bgW < MAP_WIDTH ; i++) {
			for (size_t j = 0 ; j * bgH < MAP_HEIGHT ; j++) {
				this->background.render(this->renderer, i * bgW - c.getX(), j * bgH - c.getY());
			}
		}
	}

	// Centrado
	if (this->backgroundDisplayMode == "centered") {
		if (bgW < MAP_WIDTH && bgH < MAP_HEIGHT) {
			this->background.render(this->renderer, (MAP_WIDTH - bgW) / 2 - c.getX(), (MAP_HEIGHT - bgH) / 2 - c.getY());
		} else {
			// Si la imagen es mas grande que el mapa
			// se dibuja el fondo centrado
			this->background.render(this->renderer, 0 - c.getX(), 0 - c.getY(), MAP_WIDTH, MAP_HEIGHT);
			return;
		}
	}
}

void View::WindowGame::hide(void) {
	SDL_HideWindow(this->window);
}

void View::WindowGame::show(void) {
	SDL_ShowWindow(this->window);
}