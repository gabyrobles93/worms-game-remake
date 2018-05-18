#include <iostream>
#include "model_receiver.h"

typedef char Model;

ModelReceiver::ModelReceiver(Protocol & p, Model & e) :
protocol(p),
model(e) {
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
    while (keep_runing)
        this->protocol.rcvModel(this->model);
}

void ModelReceiver::stop(void) {
    this->keep_runing = false;
}