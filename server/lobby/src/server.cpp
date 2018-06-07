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
            /* std::cout << "Esperando conexión de cliente" << std::endl; */
            Protocol newsktprotocol(std::move(this->skt.accept_connection()));
            std::string player_name;
            newsktprotocol.getPlayerName(player_name);

            cleanLobby();
            cleanQuitedClients();

            if (this->clients.find(player_name) != this->clients.end()) {
                player_name = findFreeName(player_name);
            }

            std::cout << "Bautizando al cliente como " << player_name << std::endl;
            newsktprotocol.sendName(player_name);

            /* std::cout << "Enviando games.yml al nuevo cliente." << std::endl; */
            YAML::Node match_status = this->game_status.getMatchsStatus();
            newsktprotocol.sendGameStatus(match_status);

            Client * client = new Client(std::move(newsktprotocol), player_name);
            this->clients.insert(std::pair<std::string, Client*>(player_name, client));
            LobbyAttendant * new_lobby_attendant = new LobbyAttendant(client, this->game_status, this->waiting_games);
            new_lobby_attendant->start();
            this->clients_in_lobby.insert(std::pair<std::string, LobbyAttendant*>(player_name, new_lobby_attendant));
        } catch(const SocketError & e) {
            std::cout << "Server acceptor se detiene por cierre del socket listener. " <<
            e.what() << std::endl;
            break;
        }
    }
}

void Server::cleanLobby(void) {
    std::map<std::string, LobbyAttendant*>::iterator it;
    for (it = this->clients_in_lobby.begin(); it != this->clients_in_lobby.end();) {
        if (!it->second->isRunning()) {
            it->second->join();
            std::cout << "Deleteando Lobby Attendant del cliente " << it->first << std::endl;
            delete it->second;
            this->clients_in_lobby.erase(it++);
        } else {
            ++it;
        }
    }
}

void Server::cleanQuitedClients(void) {
    std::map<std::string, Client*>::iterator it;
    for (it = this->clients.begin(); it != this->clients.end();) {
        if (it->second->getStatus() == quited) {
            std::cout << "Deleteando al cliente " << it->first << " que salio del Lobby." << std::endl;
            delete it->second;
            this->clients.erase(it++);
        } else {
            ++it;
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
        if (this->clients.find(tmp.append(number)) == this->clients.end()) {
            new_name = tmp;
            break;
        }
        counter++;
    }
    return new_name;
}