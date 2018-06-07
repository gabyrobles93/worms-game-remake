#include <iostream>
#include <fstream>
#include <string>
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
    protocol.sendGameStatus(gameStatusNode);
}

Event Client::rcvEvent(void) {
    return this->protocol.rcvEvent();
}

std::string Client::getPlayerName(void) {
    return this->player_name;
}