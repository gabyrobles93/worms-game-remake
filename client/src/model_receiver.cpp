#include <iostream>
#include <sstream>
#include <unistd.h>
#include "model_receiver.h"
#include "protected_dynamics.h"

ModelReceiver::ModelReceiver(Protocol * prot, ProtectedDynamics & dyn) :
protocol(prot),
dynamics(dyn) {
    keep_runing = true;
}

ModelReceiver::~ModelReceiver(void) {

}

bool ModelReceiver::isRunning(void) const {
    return true;
}

size_t ModelReceiver::getId(void) const {
    return 0;
}

void ModelReceiver::run(void) {
    while (this->keep_runing) {
        YAML::Node newDynamics;
        this->protocol->rcvModel(newDynamics);
        std::stringstream ss;
        ss << newDynamics;
        if (newDynamics["game_status"]) {
            if (newDynamics["game_status"]["finished"].as<int>() == 1) {
                std::cout << "La partida termino." << std::endl;
                this->keep_runing = false;
            }
        }
        this->dynamics.addModel(newDynamics);
    }
}

void ModelReceiver::stop(void) {
    this->keep_runing = false;
}