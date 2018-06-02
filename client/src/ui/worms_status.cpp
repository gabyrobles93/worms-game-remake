#include <string>
#include <SDL2/SDL.h>
#include "worms_status.h"
#include "worm.h"

View::WormsStatus::WormsStatus(YAML::Node & nodeWorms, SDL_Renderer * rend) {
	YAML::const_iterator itTeam;
	for (itTeam = nodeWorms.begin() ; itTeam != nodeWorms.end() ; itTeam++) {
		int teamId = itTeam->first.as<int>();
		const YAML::Node & eachTeam = itTeam->second["worms"];
		YAML::const_iterator itWorms;
		for (itWorms = eachTeam.begin() ; itWorms != eachTeam.end() ; itWorms++) {
			const YAML::Node & eachWorm = *itWorms;
			View::Worm * newWorm = new View::Worm(rend, eachWorm["name"].as<std::string>(), teamId, eachWorm["health"].as<int>());
			newWorm->setX(eachWorm["x"].as<int>());
			newWorm->setY(eachWorm["y"].as<int>());
			this->worms[eachWorm["id"].as<size_t>()] = newWorm;
		}
	}
}

void View::WormsStatus::render(SDL_Renderer * renderer, View::Camera & camera) {
	std::map<size_t, View::Worm *>::iterator it;

	for (it = this->worms.begin(); it != this->worms.end(); it++) {
		if (it->second->isAlive()) {
			it->second->render(renderer, camera.getX(), camera.getY());
		}
	}
}

void View::WormsStatus::update(YAML::Node wormsNode) {
	View::Worm * worm;
	YAML::const_iterator itTeam;
	for (itTeam = wormsNode.begin() ; itTeam != wormsNode.end() ; itTeam++) {
		const YAML::Node & eachTeam = itTeam->second["worms"];
		YAML::const_iterator itWorms;
		for (itWorms = eachTeam.begin() ; itWorms != eachTeam.end() ; itWorms++) {
			const YAML::Node & eachWorm = *itWorms;
			worm = this->worms[eachWorm["id"].as<size_t>()];
			worm->setX(eachWorm["x"].as<int>());
			worm->setY(eachWorm["y"].as<int>());
			worm->setHealth(eachWorm["health"].as<int>());
			worm->setMirrored(eachWorm["status"]["mirrored"].as<int>());
			worm->setWalking(eachWorm["status"]["walking"].as<int>());
			worm->setFalling(eachWorm["status"]["falling"].as<int>());
			worm->setGrounded(eachWorm["status"]["grounded"].as<int>());
		}
	}
}

View::WormsStatus::~WormsStatus(void) {
	std::map<size_t, View::Worm *>::iterator it;

	for (it = this->worms.begin(); it != this->worms.end(); it++) {
		delete it->second;
	}
}