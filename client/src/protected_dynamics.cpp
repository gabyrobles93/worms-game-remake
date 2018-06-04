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
    return this->dynamics["projectiles"];
}

int ProtectedDynamics::getTurnTimeLeft(void) {
    std::lock_guard<std::mutex> lck(this->mutex);
    return this->dynamics["game_status"]["turn_timeleft"].as<int>();
}