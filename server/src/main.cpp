
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "yaml.h"
#include "socket.h"
#include "socket_error.h"
#include "protocol.h"
#include "types.h"
#include "World.h"
#include "SnapshotPusher.h"
#include "SnapshotSender.h"
#include "blocking_queue.h"
#include "event.h"
#include "match.h"

#define PORT "8080"
#define MAP_PATH "../map.yml"
#define MAX_QUEUE_SNAPSHOTS 256
#define ROUND_DURATION_SEC 10

int main(/* int argc, char *argv[] */) try {
    SocketListener listener(PORT);
    Protocol protocol(std::move(listener.accept_connection()));
    std::string world_path(MAP_PATH);

    YAML::Node mapNode = YAML::LoadFile(world_path);
    protocol.sendGameMap(mapNode);

    World world(world_path);    
    Match match(world.getWorms(), ROUND_DURATION_SEC);
    match.printTeams();

    // Creamos hilos que sacan las fotos y las acolan (SnapshotPusher)
    // y que Mandan las fotos por socket al cliente (SnapshotSender)
    Queue<YAML::Node> models(MAX_QUEUE_SNAPSHOTS);
    SnapshotPusher snapshot_pusher(world, models);
    SnapshotSender snapshot_sender(models, protocol);

    world.start();

    // Lanzo hilos
    snapshot_pusher.start();
    snapshot_sender.start();

    match.start();

    bool quit = false;
    while(!quit) {
        Event event = protocol.rcvEvent();
        if (event.quit())
            quit = true;

       if (match.isTeamTurnOf(event.getTeamId())) {
            std::cout << "Ejecutando acción." << std::endl;
            world.executeAction(event.getAction(), match.getWormTurn(match.getTeamTurn()));
        } else {
            std::cout << "Acción ignorada." << std::endl;
        }
    }

    std::cout << "El cliente cerró la ventana." << std::endl;

    //Stops y joins de los hilos lanzados
    world.stop();
    snapshot_pusher.stop();
    snapshot_sender.stop();
    match.stop();
    snapshot_sender.join();
    snapshot_pusher.join();
    world.join();
    match.join();

    std::cout << "Server finalizado." << std::endl;
    return 0;

} catch(const SocketError & e) {
    std::cout << e.what() << std::endl;
}
