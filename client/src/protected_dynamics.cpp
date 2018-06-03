#include <mutex>
#include <sstream>
#include <iostream>
#include "protected_dynamics.h"

ProtectedDynamics::ProtectedDynamics(YAML::Node & dyn) {
    this->dynamics = dyn;
}

void ProtectedDynamics::update(YAML::Node & new_dyn) {
    std::lock_guard<std::mutex> lck(this->mutex);
    this->dynamics.reset();
    this->dynamics = new_dyn; 
}

YAML::Node ProtectedDynamics::getWorms(void) {
    std::lock_guard<std::mutex> lck(this->mutex);
    return this->dynamics["worms_teams"];
}

YAML::Node ProtectedDynamics::getProjectiles(void) {
    std::lock_guard<std::mutex> lck(this->mutex);
    //std::cout << "PROJECTILES RECEIVED: " << std::endl;
    //std::cout << this->dynamics["projectiles"] << std::endl;
    return this->dynamics["projectiles"];
}