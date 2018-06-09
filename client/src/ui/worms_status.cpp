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

void View::WormsStatus::update(const YAML::Node & wormsNode) {
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
			//worm->setSightAngle(eachWorm["sight_angle"].as<int>());
			worm->setMirrored(eachWorm["status"]["mirrored"].as<int>());
			worm->setWalking(eachWorm["status"]["walking"].as<int>());
			worm->setFalling(eachWorm["status"]["falling"].as<int>());
			worm->setGrounded(eachWorm["status"]["grounded"].as<int>());
		}
	}
}

void View::WormsStatus::updateWormProtagonic(size_t wormId) {
	std::map<size_t, View::Worm *>::const_iterator it = this->worms.begin();
	for (; it != this->worms.end() ; it++) {
		View::Worm * eachWorm = it->second;
		eachWorm->setProtagonic(it->first == wormId);
	}
}

void View::WormsStatus::updateWormsClientConfiguration(ClientConfiguration & cfg) {
	std::map<size_t, View::Worm *>::const_iterator it = this->worms.begin();
	for (; it != this->worms.end() ; it++) {
		View::Worm * eachWorm = it->second;
		eachWorm->setDataConfiguration(cfg.getWormDataConfiguration());
		eachWorm->setSightAngle(cfg.getSightAngle());
	}
}

View::WormsStatus::~WormsStatus(void) {
	std::map<size_t, View::Worm *>::iterator it;

	for (it = this->worms.begin(); it != this->worms.end(); it++) {
		delete it->second;
	}
}