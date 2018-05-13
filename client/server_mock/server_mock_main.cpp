#include <iostream>
#include <fstream>
#include <unistd.h>
#include "../src/socket.h"
#include "../src/socket_error.h"
#include "../src/protocol.h"
#include "../src/protocol_error.h"

#define LISTENING_PORT "8080"

int main(int argc, char *argv[])
try {
    SocketListener skt(LISTENING_PORT);
    Protocol protocol(skt.accept_connection());

    std::string player_name;
    protocol.getPlayerName(player_name);

    std::cout << "Welcome: " << player_name << std::endl;
    protocol.sendName(player_name);

    std::cout << "Enviado archivo de estados de juego 1." << std::endl;
    std::fstream games_status_file("games.yml", std::ifstream::in|std::ios::binary);
    protocol.sendFile(games_status_file);

    int sleep;
    sleep = 5000000;
    usleep(sleep);

    std::cout << "Enviado archivo de estados de juego 2." << std::endl;

    games_status_file.close();
    games_status_file.open("games2.yml", std::ifstream::in|std::ios::binary);
    protocol.sendFile(games_status_file);

    while(1);

} catch(const SocketError & e) {
    std::cout << e.what() << std::endl;
}
