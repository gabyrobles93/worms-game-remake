#include <mutex>
#include <map>
#include <string>
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
    std::lock_guard<std::mutex> lck(this->clients_mutex);    
    if (exists(player_name))
        return;
    
    Client new_client(std::move(protocol));
    this->clients.insert(std::pair<std::string,Client>(player_name,std::move(new_client)));
}