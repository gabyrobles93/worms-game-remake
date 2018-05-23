#include <iostream>
#include "model_receiver.h"
#include "protected_dynamics.h"

ModelReceiver::ModelReceiver(Protocol & prot, ProtectedDynamics & dyn) :
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
    while (keep_runing) {
        YAML::Node newDynamics;
        this->protocol.rcvModel(newDynamics);

        // Imprimimos snapshot recibido por cliente
        std::stringstream ss;
        ss << newDynamics;
        std::cout << "CLIENTE RECIBIO ESTE SNAPSHOOT:" << std::endl;
        std::cout << ss.str() << std::endl; 

        this->dynamics.update(newDynamics);
    }
}

void ModelReceiver::stop(void) {
    this->keep_runing = false;
}