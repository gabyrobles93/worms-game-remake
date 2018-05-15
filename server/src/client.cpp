#include <iostream>
#include <fstream>
#include "client.h"
#include "protocol.h"

Client::Client(Protocol prt) :
protocol(std::move(prt)){
    this->status = lobby;
}

void Client::sendGamesStatus(void) {
    std::fstream games_status_file("../games.yml", std::ifstream::in|std::ios::binary);
    std::cout << "Soy la conexion con el cliente y voy a enviar el games.yml" << std::endl;
    protocol.sendFile(games_status_file);    
}