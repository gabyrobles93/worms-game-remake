#include <mutex>
#include "server_lobby_feeder.h"

ServerLobbyFeeder::ServerLobbyFeeder(ServerProtectedClients & cli) :
clients(cli)
{
}

ServerLobbyFeeder::~ServerLobbyFeeder(void) {
    // Destruir serverlobbyfeeder.
}

void ServerLobbyFeeder::run(void) {
    this->keep_running = true;
    dontFeedClients();
    while (keep_running) {
        if (feed_clients) {
            // Enviar a todos los clientes el game.yml
            std::cout << "Alimento el lobby de todos los clientes" << std::endl;


            dontFeedClients();
        }
    }
}

void ServerLobbyFeeder::feedClients(void) {
    std::lock_guard<std::mutex> lck(this->feed_mutex);
    this->feed_clients = true;
}

void ServerLobbyFeeder::dontFeedClients(void) {
    std::lock_guard<std::mutex> lck(this->feed_mutex);
    this->feed_clients = false;
}

void ServerLobbyFeeder::stop(void) {
    // Stopear serverlobbyfeeder.
    this->keep_running = false;
}

bool ServerLobbyFeeder::isRunning(void) const {
    return true;
}

size_t ServerLobbyFeeder::getId(void) const {
    return 0;
}
