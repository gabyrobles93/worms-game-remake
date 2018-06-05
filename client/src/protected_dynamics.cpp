#include <mutex>
#include <sstream>
#include <iostream>
#include "protected_dynamics.h"

ProtectedDynamics::ProtectedDynamics(YAML::Node & dyn) {
    this->dynamics = dyn;
}

void ProtectedDynamics::update(YAML::Node & new_dyn) {
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