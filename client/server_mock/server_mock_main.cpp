#include <iostream>
#include <fstream>
#include "../socket.h"
#include "../socket_error.h"
#include "../protocol.h"
#include "../protocol_error.h"

#define LISTENING_PORT "8080"

int main(int argc, char *argv[])
try {
    SocketListener skt(LISTENING_PORT);
    Protocol protocol(skt.accept_connection());

    std::string player_name;
    protocol.getPlayerName(player_name);

    std::cout << "Welcome: " << player_name << std::endl;
    protocol.sendName(player_name);

    std::fstream games_status_file("games.yml");
    protocol.sendFile(games_status_file);

    std::cout << "Enviado archivo de estados de juego." << std::endl;

    while(1);

} catch(const SocketError & e) {
    std::cout << e.what() << std::endl;
}
