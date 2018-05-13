#include "server.h"
#include "socket.h"
#include "../../client/src/protocol.h"

Server::Server(std::string & config_file_path,
 std::string & port) :
skt_listener(port)
{
    clients_in_lobby_counter = 0;
    clients_in_game_counter = 0;
}

virtual void Server::run(void) {
    while (1) {
        try {
            Protocol newsktprotocol(std::move(this->skt_listener.accept_connection());
            std::string player_name;
            newsktprotocol.getPlayerName(player_name);
            if (this->clients_in_lobby.find(player_name) == this->clients_in_lobby.end()) {
                this->clients_in_lobby[player_name] = std::move(newsktprotocol);
            } else {
                player_name = findFreeName(player_name);
                newsktprotocol.sendName(player_name);
                this->clients_in_lobby[player_name] = std::move(newsktprotocol);
            }
        } catch(const SocketError & e) {
            break;
        }
        this->thread_counter++;
    }    
}

std::string Server::findFreeName(std::string & old_name) const{
    int counter = 1;
    std::string number;
    std::string new_name;
    while(1) {
        number.clear();
        number.append("-" + std::to_string(counter));
        if (this->clients_in_lobby.find(old_name.append(number)) == this->clients_in_lobby.end()) {
            new_name = old_name + number;
            break;
        }
        counter++;
    }
    return new_name;
}