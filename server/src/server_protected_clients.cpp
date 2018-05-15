#include <mutex>
#include <map>
#include <string>
#include <fstream>
#include "server_protected_clients.h"
#include "protocol.h"
#include "client.h"

bool ServerProtectedClients::exists(std::string & client_name) {
    std::lock_guard<std::mutex> lck(this->clients_mutex);
    if (this->clients.find(client_name) != this->clients.end())
        return true;
    return false;
}

void ServerProtectedClients::addClient(std::string & player_name, Protocol protocol) {
    if (exists(player_name))
        return;
    std::lock_guard<std::mutex> lck(this->clients_mutex);    
    
    Client new_client(std::move(protocol));
    this->clients.insert(std::pair<std::string,Client>(player_name,std::move(new_client)));
}

void ServerProtectedClients::sendGamesStatus(std::string & player_name) {
    if (!exists(player_name))
        return;
    this->clients.find(player_name)->second.sendGamesStatus();
}