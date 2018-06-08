#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "client.h"
#include "protocol.h"
#include "event.h"
#include "yaml.h"

Client::Client(Protocol prt, std::string & pn) :
protocol(std::move(prt)){
    this->player_name = pn;
    this->status = lobby;
}

void Client::sendGamesStatus(YAML::Node gameStatusNode) {
    std::cout << "Soy la conexion con el cliente y voy a enviar el games.yml" << std::endl;
    std::stringstream ss;
    ss << gameStatusNode;
    std::cout << ss.str() << std::endl;
    protocol.sendGameStatus(gameStatusNode);
}

Event Client::rcvEvent(void) {
    return this->protocol.rcvEvent();
}

std::string Client::getPlayerName(void) {
    return this->player_name;
}

void Client::setStatus(client_status_t new_status) {
    this->status = new_status;
}

client_status_t Client::getStatus(void) {
    return this->status;
}