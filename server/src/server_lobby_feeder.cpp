#include "server_lobby_feeder.h"

ServerLobbyFeeder::ServerLobbyFeeder(ServerProtectedClients & cli) :
clients(cli)
{
}

ServerLobbyFeeder::~ServerLobbyFeeder(void) {
    // Destruir serverlobbyfeeder.
}

void ServerLobbyFeeder::run(void) {
    
}

void ServerLobbyFeeder::stop(void) {
    // Stopear serverlobbyfeeder.
}

bool ServerLobbyFeeder::isRunning(void) const {
    return true;
}

size_t ServerLobbyFeeder::getId(void) const {
    return 0;
}