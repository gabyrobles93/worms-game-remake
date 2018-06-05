#include <mutex>
#include <sstream>
#include <iostream>
#include "protected_dynamics.h"

ProtectedDynamics::ProtectedDynamics(YAML::Node & dyn) {
    this->dynamics = dyn;
}

void ProtectedDynamics::addModel(YAML::Node & new_dyn) {
    // No deberia matar el nodo, este ProtectedDynamics
    // deberia tener una cola bloqueante de snapshoots
    // Quien pushea es el Model Receiver
    // Quien popea es el cliente en su hilo main.
    // Opcional: se puede popear un "SnapShoot" en vez
    // de popear un Nodo YAML "dynamics" y entonces
    // implementar el getWorms(), getTimeLeft(), getTuMadre()
    // en la clase Snapshoot y estos metodos te devolverian
    // los nodos YAML corrrespondiente como lo esta haciendo
    // ProtectedDynamics
/*     this->dynamics.reset();
    this->dynamics = new_dyn;  */
    this->models.push(new_dyn);
}

void ProtectedDynamics::popModel(void) {
    if (!this->models.empty()) {
        this->dynamics = this->models.front();
        this->models.pop();
    }
}

YAML::Node ProtectedDynamics::getWorms(void) {
    return this->dynamics["worms_teams"];
}

YAML::Node ProtectedDynamics::getProjectiles(void) {
    return this->dynamics["projectiles"];
}

int ProtectedDynamics::getTurnTimeLeft(void) {
    if (this->dynamics["game_status"]) {
        return this->dynamics["game_status"]["turn_timeleft"].as<int>();
    }
    return -1;
}

size_t ProtectedDynamics::getWormProtagonicId(void) {
    return this->dynamics["game_status"]["protagonic_worm"].as<size_t>();
}