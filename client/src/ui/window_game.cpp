#include <vector>
#include <iterator>
#include "window_game.h"
#include "yaml.h"
#include "worm.h"
#include "camera.h"

#define WATER_LEVEL 300

View::WindowGame::WindowGame(YAML::Node & staticNode, int w, int h) : staticMap(staticNode) {
	this->screen_width = w;
	this->screen_height = h;
	this->init();
	this->background.loadFromFile(this->staticMap["background"][0]["file"].as<std::string>(), renderer);
	this->loadStaticObjects();
	this->water.init(
		this->renderer,
		0,
		this->background.getHeight() - WATER_LEVEL,
		this->background.getWidth(),
		this->background.getHeight(),
		PATH_WATER_2
	);
}

void View::WindowGame::loadStaticObjects(void) {
	const YAML::Node & nodeShortGirders = this->staticMap["short_girders"];
	const YAML::Node & nodeLongGirders = this->staticMap["long_girders"];
	YAML::const_iterator it;

	for (it = nodeShortGirders.begin() ; it != nodeShortGirders.end() ; it++) {
		const YAML::Node & eachGirder = *it;
/* 		std::cout << "Nueva viga corta: " << std:: endl;
		std::cout << "Angulo: " << eachGirder["angle"].as<int>() << std::endl;
		std::cout << "Pos X: " << eachGirder["x"].as<int>() << std::endl;
		std::cout << "Pos Y: " << eachGirder["y"].as<int>() << std::endl; */
		View::GirderShort * newShortGirder = new View::GirderShort(this->renderer, eachGirder["angle"].as<int>());
		newShortGirder->setX(eachGirder["x"].as<int>());
		newShortGirder->setY(eachGirder["y"].as<int>());
		this->shortGirders.push_back(newShortGirder);
	}

	for (it = nodeLongGirders.begin() ; it != nodeLongGirders.end() ; it++) {
		const YAML::Node & eachGirder = *it;
/* 		std::cout << "Nueva viga larga: " << std:: endl;
		std::cout << "Angulo: " << eachGirder["angle"].as<int>() << std::endl;
		std::cout << "Pos X: " << eachGirder["x"].as<int>() << std::endl;
		std::cout << "Pos Y: " << eachGirder["y"].as<int>() << std::endl; */
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
            SDL_WINDOW_SHOWN
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
	return this->background.getWidth();
}

int View::WindowGame::getBgHeight(void) const {
	return this->background.getHeight();
}

void View::WindowGame::render(View::Camera & camera) {
	SDL_Rect cam = camera.getCamera();
	this->background.render(this->renderer, 0, 0, &cam);

	std::vector<View::GirderLong *>::iterator it_l;
	for (it_l = this->longGirders.begin(); it_l != this->longGirders.end(); it_l++) {
		(*it_l)->render(this->renderer, camera.getX(), camera.getY());
	}

	std::vector<View::GirderShort *>::iterator it_s;
	for (it_s = this->shortGirders.begin(); it_s != this->shortGirders.end(); it_s++) {
		(*it_s)->render(this->renderer, camera.getX(), camera.getY());
	}

	this->water.render(this->renderer, camera.getX(), camera.getY());
}