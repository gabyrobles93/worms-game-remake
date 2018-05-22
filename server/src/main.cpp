
#include <iostream>
#include <sstream>
#include <string>
#include "yaml.h"
#include "socket.h"
#include "socket_error.h"
#include "protocol.h"
#include "types.h"
#include "World.h"
#include "SnapshotPusher.h"
#include "SnapshotSender.h"
#include "blocking_queue.h"

#define PORT "8080"
#define MAP_PATH "../map.yml"

int main(/* int argc, char *argv[] */) try {
    SocketListener listener(PORT);
    Protocol protocol(std::move(listener.accept_connection()));
    YAML::Node mapNode = YAML::LoadFile(MAP_PATH);
    World world(mapNode);

    BlockingQueue<YAML::Node> models;
    SnapshotPusher snapshot_pusher(world, models);
    SnapshotSender snapshot_sender(models, protocol);
    protocol.sendGameMap(mapNode);
    std::cout << "Mapa enviado" << std::endl;

    world.start();
    std::cout << "Corriendo mundo" << std::endl;

    world.getSnapshot();
    //snapshot_pusher.start();

    //snapshot_sender.start();
    //std::cout << "Enviando snapshot" << std::endl;

    bool quit = false;
    while(!quit) {
        action_t event = a_noEvent;
        std::cout << "Esperando evento del cliente." << std::endl;
        protocol.rcvEvent(event);
        std::cout << "El cliente envió el evento " << event << std::endl;
        if (event == a_quitGame)
            quit = true;
    }

    std::cout << "EL CLIENTE CERRO LA VENTaNA" << std::endl;
    world.stop();
    //snapshot_pusher.stop();
    //snapshot_sender.stop();

    //snapshot_sender.join();
    //snapshot_pusher.join();
    
    std::cout << "HACIENDO JOIN" << std::endl;
    world.join();
    std::cout << "MUNDO JOINEADO" <<std::endl;
    return 0;

} catch(const SocketError & e) {
    std::cout << e.what() << std::endl;
}