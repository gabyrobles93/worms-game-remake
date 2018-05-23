#include <string>
#include <SDL2/SDL.h>
#include "worms_status.h"
#include "worm.h"

View::WormsStatus::WormsStatus(YAML::Node & nodeWorms, SDL_Renderer * rend) {
	YAML::const_iterator it;
	for (it = nodeWorms.begin() ; it != nodeWorms.end() ; it++) {
		const YAML::Node & eachWorm = *it;
		View::Worm * newWorm = new View::Worm(rend, eachWorm["name"].as<std::string>(), eachWorm["team"].as<size_t>(), eachWorm["health"].as<int>());
		newWorm->setX(eachWorm["x"].as<int>());
		newWorm->setY(eachWorm["y"].as<int>());
		this->worms[eachWorm["id"].as<size_t>()] = newWorm;
	}
}

void View::WormsStatus::render(SDL_Renderer * renderer, View::Camera & camera) {
	std::map<size_t, View::Worm *>::iterator it;

	for (it = this->worms.begin(); it != this->worms.end(); it++) {
		if (it->second->isAlive()) {
			//it->second->setX(it->second->getX()+1); // Para mover los gusanos y debuggear
			it->second->render(renderer, camera.getX(), camera.getY());
		}
	}
}

void View::WormsStatus::update(YAML::Node wormsNode) {
	View::Worm * worm;
	YAML::const_iterator it;
	for (it = wormsNode.begin() ; it != wormsNode.end() ; it++) {
		const YAML::Node & eachWorm = *it;
		worm = this->worms[eachWorm["id"].as<size_t>()];
		worm->setX(eachWorm["x"].as<int>());
		worm->setY(eachWorm["y"].as<int>());
	}
}

View::WormsStatus::~WormsStatus(void) {
	std::map<size_t, View::Worm *>::iterator it;

	for (it = this->worms.begin(); it != this->worms.end(); it++) {
		delete it->second;
	}
}