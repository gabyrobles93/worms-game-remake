#include <mutex>
#include <sstream>
#include <iostream>
#include "protected_dynamics.h"

ProtectedDynamics::ProtectedDynamics(YAML::Node & dyn) {
    this->dynamics = dyn;
}

void ProtectedDynamics::addModel(YAML::Node & new_dyn) {
    this->models.push(new_dyn);
}

bool ProtectedDynamics::popModel(void) {
    bool thereIsModel = this->models.size() != 0;
    if (this->models.size()) {
        this->dynamics.reset();
        this->dynamics = this->models.front();
        this->models.pop();
    }
    return thereIsModel;
}

bool ProtectedDynamics::finishedMatch(void) {
    bool end_match = false;
    if (this->dynamics["game_status"]) {
        end_match = this->dynamics["game_status"]["finished"].as<int>();
    }
    return end_match;
}

YAML::Node ProtectedDynamics::getWorms(void) {
    const YAML::Node & teams = this->dynamics["worms_teams"];
    return teams;
}

YAML::Node ProtectedDynamics::getProjectiles(void) {
    const YAML::Node & projectiles = this->dynamics["projectiles"];
    return projectiles;
}

YAML::Node ProtectedDynamics::getGameStatus(void) {
    const YAML::Node & game_status = this->dynamics["game_status"];
    return game_status;
}

YAML::Node ProtectedDynamics::getTeamInventory(void) {
    // FIXME: cuando tengamos el team id devolvemos el inventory correspondiente
    const YAML::Node & game_status = this->dynamics["game_status"];
    return game_status;
}

int ProtectedDynamics::getTurnTimeLeft(void) {
    if (this->dynamics["game_status"]) {
        return this->dynamics["game_status"]["turn_timeleft"].as<int>();
    }
    return -1;
}

size_t ProtectedDynamics::getWormProtagonicId(void) {
    if (this->dynamics["game_status"]) {
        return this->dynamics["game_status"]["protagonic_worm"].as<size_t>();
    }
    return 1;
}

bool ProtectedDynamics::hasGameStatus(void) {
    if (this->dynamics["game_status"]) {
        return true;
    }
    return false;
}