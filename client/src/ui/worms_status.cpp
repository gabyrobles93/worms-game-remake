#include "worms_status.h"

View::WormsStatus::WormsStatus(YAML::Node & mapNode) :
dynamicMap(mapNode) {
	const YAML::Node & nodeWorms = this->dynamicMap["worms"];
	YAML::const_iterator it;

	for (it = nodeWorms.begin() ; it != nodeWorms.end() ; it++) {
		const YAML::Node & eachGirder = *it;
/* 		std::cout << "Nueva viga corta: " << std:: endl;
		std::cout << "Angulo: " << eachGirder["angle"].as<int>() << std::endl;
		std::cout << "Pos X: " << eachGirder["x"].as<int>() << std::endl;
		std::cout << "Pos Y: " << eachGirder["y"].as<int>() << std::endl; */
		View::Worm * newWorm = new View::Worm();
		newShortGirder->setX(eachGirder["x"].as<int>());
		newShortGirder->setY(eachGirder["y"].as<int>());
		this->shortGirders.push_back(newShortGirder);
	}
}

