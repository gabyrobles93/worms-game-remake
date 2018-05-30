
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <unistd.h>
#include "yaml.h"
#include "socket.h"
#include "socket_error.h"
#include "protocol.h"
#include "types.h"
#include "World.h"
#include "snapshot_sender.h"
#include "blocking_queue.h"
#include "event.h"
#include "match.h"
#include "event_receiver.h"

#define PORT "8080"
#define MAP_PATH "../map2.yml"
#define MAX_QUEUE_SNAPSHOTS 256
#define TURN_DURATION_SEC 5

int main(/* int argc, char *argv[] */) try {
    SocketListener listener(PORT);
    Protocol protocol(std::move(listener.accept_connection()));
    std::string world_path(MAP_PATH);

    YAML::Node mapNode = YAML::LoadFile(world_path);
    protocol.sendGameMap(mapNode);

    Queue<YAML::Node> snapshots(MAX_QUEUE_SNAPSHOTS);
    World world(world_path, snapshots);    
    Match match(world.getWorms(), TURN_DURATION_SEC);
    match.printTeams();

    // Creamos hilos que sacan las fotos y las acolan (SnapshotPusher)
    // y que Mandan las fotos por socket al cliente (SnapshotSender)
    SnapshotSender snapshot_sender(snapshots, protocol);
    EventReceiver event_receiver(protocol, world, 1);

    // Lanzo hilos
    world.start();
    snapshot_sender.start();
    event_receiver.start();
    
    unsigned int timer = 0;
    match.start(world.getTimeSeconds()); //NO LANZA UN HILO, EMPIEZA LA PARTIDA.
    while(!event_receiver.quitEvent() && !match.finished()) {
        usleep(15000);
        timer = world.getTimeSeconds();
        std::cout << timer << " Segundos." << std::endl;
        match.update(timer);
    }

    std::cout << "El cliente cerró la ventana." << std::endl;

    //Stops y joins de los hilos lanzados
    world.stop();
    snapshot_sender.stop();
    event_receiver.stop();
    snapshot_sender.join();
    world.join();
    event_receiver.join();

    std::cout << "Server finalizado." << std::endl;
    return 0;

} catch(const SocketError & e) {
    std::cout << e.what() << std::endl;
}
