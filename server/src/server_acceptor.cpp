#include <iostream>
#include <string>
#include "server_acceptor.h"
#include "server_protected_clients.h"
#include "../../client/src/protocol.h"
#include "socket_error.h"

ServerAcceptor::ServerAcceptor(std::string & port, ServerProtectedClients & cli) :
skt(port),
clients(cli)
{
}

 void ServerAcceptor::run(void) {
    while (1) {
        try {
            Protocol newsktprotocol(std::move(this->skt.accept_connection()));
            std::string player_name;
            newsktprotocol.getPlayerName(player_name);
            if (this->clients.exists(player_name) == true) {
                player_name = findFreeName(player_name);
                newsktprotocol.sendName(player_name);
                this->clients.addClient(player_name, std::move(newsktprotocol));
            }
            this->clients.addClient(player_name, std::move(newsktprotocol));
        } catch(const SocketError & e) {
            std::cout << "Server acceptor se detiene por cierre del socket listener. " <<
            e.what() << std::endl;
            break;
        }
    }    
}

std::string ServerAcceptor::findFreeName(std::string & old_name) const {
    int counter = 1;
    std::string number;
    std::string new_name;
    while(1) {
        number.clear();
        number.append("-" + std::to_string(counter));
        if (this->clients.exists(old_name.append(number)) == false) {
            new_name = old_name + number;
            break;
        }
        counter++;
    }
    return new_name;
}
