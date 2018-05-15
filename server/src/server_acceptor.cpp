#include <iostream>
#include <string>
#include "server_acceptor.h"
#include "server_protected_clients.h"
#include "protocol.h"
#include "socket_error.h"

ServerAcceptor::ServerAcceptor(std::string & port, ServerProtectedClients & cli) :
skt(port),
clients(cli)
{
}

 void ServerAcceptor::run(void) {
    while (1) {
        try {
            std::cout << "Esperando conexión de cliente" << std::endl;
            Protocol newsktprotocol(std::move(this->skt.accept_connection()));
            std::cout << "Cliente conectado!" << std::endl;
            std::string player_name;
            newsktprotocol.getPlayerName(player_name);
            std::cout << "Cliente quiere llamarse " << player_name << std::endl;
             if (this->clients.exists(player_name) == true) {
                player_name = findFreeName(player_name);
                std::cout << "Cliente renombrado!" << std::endl;
            }
            std::cout << "Bautizando al cliente como " << player_name << std::endl;
            newsktprotocol.sendName(player_name);

            std::cout << "Agregando a " << player_name << " a la lista de clientes." << std::endl;
            this->clients.addClient(player_name, std::move(newsktprotocol));

            std::cout << "Enviando games.yml al nuevo cliente." << std::endl;
            this->clients.sendGamesStatus(player_name);
            
        } catch(const SocketError & e) {
            std::cout << "Server acceptor se detiene por cierre del socket listener. " <<
            e.what() << std::endl;
            break;
        }
    }    
}

void ServerAcceptor::stop(void) {
    // Stopear aceptador
    this->skt.stopListening();
}

std::string ServerAcceptor::findFreeName(std::string & old_name) const {
    int counter = 1;
    std::string number;
    std::string new_name;
    std::string tmp;
    while(1) {
        number.clear();
        number.append("-" + std::to_string(counter));
        tmp = old_name;
        if (this->clients.exists(tmp.append(number)) == false) {
            new_name = tmp;
            break;
        }
        counter++;
    }
    return new_name;
}

ServerAcceptor::~ServerAcceptor(void) {
    // Cerrar server acceptor ordenadamente  
}

bool ServerAcceptor::isRunning(void) const {
    return true;
}

size_t ServerAcceptor::getId(void) const {
    return 0;
}