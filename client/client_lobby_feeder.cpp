#include <QTableWidget>
#include <iostream>
#include "thread.h"
#include "protocol.h"
#include "client_lobby_feeder.h"
#include "socket_error.h"
#include "protocol_error.h"

ClientLobbyFeeder::ClientLobbyFeeder(Protocol & prot, QTableWidget* table) :
protocol(prot),
games_table(table) {
    std::cout << "Lobby feeder creado" << std::endl;
    this->running = true;
}

ClientLobbyFeeder::~ClientLobbyFeeder(void) {
    std::cout << "Destruyendo lobby feeder." << std::endl;
}

void ClientLobbyFeeder::run(void) {
    while(1) {
         try {
            this->games_status.open("games.yml", std::ios::out|std::ios::binary|std::ios::trunc);
            std::cout << "Esperando archivo de game status." << std::endl;
            this->protocol.rcvFile(this->games_status);
            std::cout << "Recibido archivo de estados de juego." << std::endl;
            feedGamesTable();
        } catch(const ProtocolError & e) {
            std::cout << "Fin del ciclo de lobby feeder. " << std::endl;
            break;
        }       
    }

    this->running = false;
}

void ClientLobbyFeeder::stop(void) {
    std::cout << "Haciendo shutdown de socket lobby feeder." << std::endl;
    this->protocol.sendExitLobby();
}

void ClientLobbyFeeder::feedGamesTable(void) {
    std::cout << "Actualizo tabla de lobby." << std::endl;
}

bool ClientLobbyFeeder::isRunning(void) const {
    return this->running;
}
size_t ClientLobbyFeeder::getId(void) const {
    return 0;
}