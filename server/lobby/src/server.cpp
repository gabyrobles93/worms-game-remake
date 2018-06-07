#include <fstream>
#include <map>
#include <sstream>
#include "server.h"
#include "socket.h"
#include "socket_error.h"
#include "protocol.h"
#include "server_error.h"
#include "client.h"
#include "lobby_attendant.h"

Server::Server(std::string & config_file_path, std::string & port) :
skt(port) {
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
/*             if (this->clients.exists(player_name) == true) {
                player_name = findFreeName(player_name);
            } */
            std::cout << "Bautizando al cliente como " << player_name << std::endl;
            newsktprotocol.sendName(player_name);
/*             this->clients.addClient(player_name, std::move(newsktprotocol)); */

            std::cout << "Enviando games.yml al nuevo cliente." << std::endl;
            YAML::Node match_status = this->game_status.getMatchsStatus();
            newsktprotocol.sendGameStatus(match_status);

            Client * client = new Client(std::move(newsktprotocol), player_name);
            this->clients.insert(std::pair<std::string, Client*>(player_name, client));
            LobbyAttendant * new_lobby_attendant = new LobbyAttendant(client, this->game_status);
            new_lobby_attendant->start();
            this->clients_in_lobby.insert(std::pair<std::string, LobbyAttendant*>(player_name, new_lobby_attendant));
            cleanFinishedClients();
        } catch(const SocketError & e) {
            std::cout << "Server acceptor se detiene por cierre del socket listener. " <<
            e.what() << std::endl;
            break;
        }
    }
}

void Server::cleanFinishedClients(void) {

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
}

 bool Server::isRunning(void) const {
     return this->keep_running;
 }

Server::~Server(void) {
    // Cerrar server ordenadamente
    std::map<std::string, Client*>::iterator it;
    for (it = this->clients.begin(); it != this->clients.end(); it++) {
        delete it->second;
    }
}

size_t  Server::getId(void) const{
    return 0;
}

void Server::stop(void) {
    // Stopear servidor.
    // Seguramente haya que cerrar los sockets ordenadamente. 
    this->keep_running = false;
}

std::string Server::findFreeName(std::string & old_name) {
    int counter = 1;
    std::string number;
    std::string new_name;
    std::string tmp;
    while(1) {
        number.clear();
        number.append("-" + std::to_string(counter));
        tmp = old_name;
/*         if (this->clients.exists(tmp.append(number)) == false) {
            new_name = tmp;
            break;
        } */
        counter++;
    }
    return new_name;
}