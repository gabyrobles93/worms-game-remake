#include <fstream>
#include <sstream>
#include "server.h"
#include "socket.h"
#include "socket_error.h"
#include "server_acceptor.h"
#include "protocol.h"
#include "server_error.h"

Server::Server(std::string & config_file_path,
 std::string & port) :
acceptor(port, clients),
feeder(clients)
{
    loadConfigFile(config_file_path);
    this->keep_running = true;
}

void Server::run(void) {
    while (1) {
        try {
            std::cout << "Esperando conexión de cliente" << std::endl;
            Protocol newsktprotocol(std::move(this->skt.accept_connection()));
            std::string player_name;
            newsktprotocol.getPlayerName(player_name);
             if (this->clients.exists(player_name) == true) {
                player_name = findFreeName(player_name);
            }
            std::cout << "Bautizando al cliente como " << player_name << std::endl;
            newsktprotocol.sendName(player_name);
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

void Server::loadConfigFile(std::string & config_file_path) {
    std::fstream cfg_file(config_file_path, std::ios::in);
    if (!cfg_file.is_open()) {
        std::stringstream msg;
        msg << MSG_CANT_OPEN_CFG_FILE << " " << config_file_path;
        throw ServerError(msg.str());
    }
    std::string line;
    std::getline(cfg_file, line);
    std::cout << line << std::endl;
    std::cout << cfg_file;
}

 bool Server::isRunning(void) const {
     return this->keep_running;
 }

Server::~Server(void) {
    // Cerrar server ordenadamente
}

size_t  Server::getId(void) const{
    return 0;
}

void Server::stop(void) {
    // Stopear servidor.
    // Seguramente haya que cerrar los sockets ordenadamente. 
    this->keep_running = false;
}

std::string Server::findFreeName(std::string & old_name) const {
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