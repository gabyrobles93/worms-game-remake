
#include <iostream>
#include <sstream>
#include "yaml.h"
#include "socket.h"
#include "socket_error.h"
#include "protocol.h"
#include "types.h"
#include "World.h"

#define PORT "8080"
#define MAP_PATH "../map.yml"

int main(/* int argc, char *argv[] */) try {
    SocketListener listener(PORT);
    Protocol protocol(std::move(listener.accept_connection()));
    YAML::Node mapNode = YAML::LoadFile(MAP_PATH);
    World world(mapNode);

    protocol.sendGameMap(mapNode);
    std::cout << "Mapa enviado" << std::endl;
    bool quit = false;
    while(!quit) {
        action_t event = a_noEvent;
        std::cout << "Esperando evento del cliente." << std::endl;
        protocol.rcvEvent(event);
        std::cout << "El cliente envió el evento " << event;
        if (event == a_quitGame)
            quit = true;
    }

    return 0;

} catch(const SocketError & e) {
    std::cout << e.what() << std::endl;
}