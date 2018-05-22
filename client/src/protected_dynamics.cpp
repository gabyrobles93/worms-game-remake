#include <mutex>
#include <iostream>
#include "protected_dynamics.h"

ProtectedDynamics::ProtectedDynamics(YAML::Node & dyn) {
    this->dynamics = dyn;
}

void ProtectedDynamics::update(YAML::Node & new_dyn) {
    std::lock_guard<std::mutex> lck(this->mutex);

    YAML::Node::const_iterator it;
    for (it = new_dyn["worms"].begin(); it != new_dyn["worms"].end(); it++) {
        std::cout << "Worm: " << (*it)["name"].as<std::string>() << std::endl;
        std::cout << "X: " << (*it)["x"].as<std::string>() << std::endl;
        std::cout << "Y: " << (*it)["y"].as<std::string>() << std::endl;
    }

    this->dynamics = new_dyn;
}

YAML::Node ProtectedDynamics::getWorms(void) {
    std::lock_guard<std::mutex> lck(this->mutex);
    return this->dynamics["worms"];
}