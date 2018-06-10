#include "waiting_match.h"
#include "thread.h"
#include "protocol.h"
#include "yaml.h"

WaitingMatch::WaitingMatch(Protocol * p) :
protocol(p) {
    this->keep_running = true;
}

bool WaitingMatch::isRunning(void) const {
    return this->keep_running;
}

void WaitingMatch::run(void) {
    while (keep_running) {
        YAML::Node msg;
        this->protocol->rcvMsg(msg);

        std::cout << "Mensaje del servidor recibido en una waiting match:" << std::endl;
        std::stringstream ss;
        ss << msg;
        std::cout << ss.str() << std::endl;

        if (msg["code"].as<int>() == 1) {
            if (msg["msg"].as<std::string>() == "exited") {
                std::cout << "El hoster te dio el ok para que salgas de la partida.." << std::endl;
                this->keep_running = false;
                return;
            }
            if (msg["msg"].as<std::string>() == "started") {
                std::cout << "El hoster decidio que la partida empieza ahora!" << std::endl;
            }
        } else if (msg["code"].as<int>() == 0) {
            if (msg["msg"].as<std::string>() == "aborted") {
                std::cout << "El hoster decidió cancelar la partida en espera." << std::endl;
                this->keep_running = false;
                return;
            }
        }
    }
}

void WaitingMatch::stop(void) {
    this->keep_running = false;
}

size_t WaitingMatch::getId(void) const {
    return 0;
}