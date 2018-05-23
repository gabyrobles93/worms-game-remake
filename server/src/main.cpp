
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
    std::string world_path(MAP_PATH);
    World world(world_path);

    // Creamos hilos que sacan las fotos y las acolan (SnapshotPusher)
    // y que Mandan las fotos por socket al cliente (SnapshotSender)
    BlockingQueue<YAML::Node> models;
    SnapshotPusher snapshot_pusher(world, models);
    SnapshotSender snapshot_sender(models, protocol);

    YAML::Node mapNode = YAML::LoadFile(world_path);
    protocol.sendGameMap(mapNode);

    world.start();

    // Lanzo hilos
    snapshot_pusher.start();
    snapshot_sender.start();

    bool quit = false;
    while(!quit) {
        action_t event = a_noEvent;
        std::cout << "Esperando evento del cliente." << std::endl;
        protocol.rcvEvent(event);
        std::cout << "El cliente envió el evento " << event << std::endl;
        if (event == a_quitGame)
            quit = true;
    }

    std::cout << "El cliente cerró la ventana." << std::endl;

    //Stops y joins de los hilos lanzados
    world.stop();
    snapshot_pusher.stop();
    snapshot_sender.stop();
    snapshot_sender.join();
    snapshot_pusher.join();
    world.join();

    std::cout << "Server finalizado." << std::endl;
    return 0;

} catch(const SocketError & e) {
    std::cout << e.what() << std::endl;
}