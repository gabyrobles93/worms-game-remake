
#include <iostream>
#include "yaml.h"
#include "socket.h"
#include "socket_error.h"
#include "protocol.h"
#include "types.h"

#define PORT "8080"
#define MAP_PATH "../map.yml"

int main(/* int argc, char *argv[] */) try {
    SocketListener listener(PORT);
    Protocol protocol(std::move(listener.accept_connection()));
    YAML::Node mapNode = YAML::Load(MAP_PATH);

    protocol.sendGameMap(mapNode);

    bool quit = false;
    while(!quit) {
        action_t event = a_noEvent;
        protocol.rcvEvent(event);
        std::cout << "El cliente envió el evento " << event;
        if (event == a_quitGame)
            quit = true;
    }

    return 0;
} catch(const SocketError & e) {
    std::cout << e.what() << std::endl;
}