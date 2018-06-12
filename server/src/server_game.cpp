#include <string>
#include <unistd.h>
#include "server_game.h"
#include "protocol.h"
#include "yaml.h"
#include "blocking_queue.h"
#include "World.h"
#include "match.h"
#include <fstream>
#include "snapshot_sender.h"
#include "event_receiver.h"

#define MAX_QUEUE_SNAPSHOTS 256
#define MAP_YML_NAME "map.yml"

ServerGame::ServerGame(std::vector<Client*> cl, std::string & map_path) :
clients(cl),
map_path(map_path) {
    std::vector<Client*>::const_iterator it;
    // Envio a todos los clientes el mapa del juego.
    std::fstream file_map(this->map_path, std::fstream::in | std::fstream::binary);
    for (it = this->clients.begin(); it != this->clients.end(); it++) {
        std::cout << "Iterando por clientes." << std::endl;
        if ((*it)->getIdInMatch() == 1) continue;
        std::cout << "Enviándole el mapa al jugador nro. " << (*it)->getIdInMatch() << std::endl;
        (*it)->sendMapGame(file_map);
    }
    std::string map_yml_name(MAP_YML_NAME);
	std::string cmd_unzip_tar_gz = "tar -xf " + map_path;
	std::system(cmd_unzip_tar_gz.c_str());
}

void ServerGame::startGame(void) {
    std::cout << "Inicio de server game." << std::endl;
    Queue<Snapshot*> snapshots(MAX_QUEUE_SNAPSHOTS);
    std::cout << "Creando world." << std::endl;
    std::string map_yml_name(MAP_YML_NAME);
    World world(map_yml_name, snapshots);  
    std::cout << "Creando match." << std::endl;  
    Match match(world.getWorms(), world.getTeams(), world.getWind(), gConfiguration.TURN_DURATION);
    std::cout << "Creando snapshot sender." << std::endl;
    SnapshotSender snapshot_sender(snapshots, match, this->clients);
    
    std::cout << "Lanzando hilos." << std::endl;
    std::vector<EventReceiver*> event_receiver;
    std::vector<Client*>::const_iterator it;
    for (it = this->clients.begin(); it != this->clients.end(); it++) {
        event_receiver.push_back(new EventReceiver((*it), world, match, (*it)->getIdInMatch()));
    }

    world.start();
    snapshot_sender.start();
    //Lanzo hilos de event receiver
    std::vector<EventReceiver*>::const_iterator it2;
    for (it2 = event_receiver.begin(); it2 != event_receiver.end(); it2++) {
        (*it2)->start();
    }

    std::cout << "Inicio de game loop de servidor." << std::endl;
    gameLoop(match, world);
    std::cout << "Fin de game loop de servidor." << std::endl;

    if (match.finished()) {
        std::cout << "La partida finalizó y el ganador es " << match.getWinner() << std::endl;
    }

    snapshot_sender.stop();
    std::cout << "Snapshot sender stopeado" << std::endl;
    //Stops y joins de los hilos lanzados
    world.stop();
    world.join();
    snapshot_sender.join();
    std::cout << "World stopeado y joineado." << std::endl;
    for (it2 = event_receiver.begin(); it2 != event_receiver.end(); it2++) {
        (*it2)->stop();
    }
    for (it2 = event_receiver.begin(); it2 != event_receiver.end(); it2++) {
        (*it2)->join();
    }

    std::cout << "Fin de server game." << std::endl;
}

void ServerGame::gameLoop(Match & match, World & world) {
    unsigned int timer = 0;
    match.start(world.getTimeSeconds());
    while(!match.finished()) {
        timer = world.getTimeSeconds();
        match.setAliveProjectilesFlag(world.hasAliveProjectiles());
        match.setMovingWormsFlag(world.hasWormsMoving());
        match.setWormsAffectedByExplosion(world.hasWormsAffectedByExplosion());
        match.setProtagonicWormGotHurt(world.hasWormGotHurt(match.getWormTurn(match.getTeamTurn())));
        match.setProtagonicWormDidShoot(world.hasWormShooted(match.getWormTurn(match.getTeamTurn())));
        usleep(16666);
        match.update(world.getTimeSeconds() - timer);
    }
}