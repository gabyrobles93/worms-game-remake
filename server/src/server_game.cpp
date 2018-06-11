#include <string>
#include "server_game.h"
#include "protocol.h"
#include "yaml.h"
#include "blocking_queue.h"
#include "World.h"
#include "match.h"
#include "snapshot_sender.h"
#include "event_receiver.h"

ServerGame::ServerGame(std::vector<Client*> cl, std::string & map_path) :
clients(cl),
mapNode(YAML::LoadFile(map_path)) {
    std::vector<Client*>::const_iterator it;
    // Envio a todos los clientes el mapa del juego.
    for (it = this->clients.begin(); it != this->clients.end(); it++) {
        (*it)->sendGameMap(this->mapNode);
    }
}

void ServerGame::startGame(void) {
    Queue<Snapshot*> snapshots(MAX_QUEUE_SNAPSHOTS);
    World world(world_path, snapshots);    
    Match match(world.getWorms(), world.getTeams(), world.getWind(), gConfiguration.TURN_DURATION);
    SnapshotSender snapshot_sender(snapshots, match, this->clients);
    
    std::vector<EventReceiver*> event_receiver;
    std::vector<Client*>::const_iterator it;
    for (it = this->clients.begin(); it != this->clients.end(); it++) {
        event_receiver.push_back(new EventReceiver((*it), world, match, (*it)->getInMatchId()));
    }

    world.start();
    snapshot_sender.start();
    //Lanzo hilos de event receiver
    std::vector<EventReceiver*>::const_iterator it2;
    for (it2 = event_receiver.begin(); it2 = event_receiver.end(); it2++) {
        (*it2)->start();
    }

    std::cout << "Inicio de game loop de servidor." << std::endl;
    gameLoop();
    std::cout << "Fin de game loop de servidor." << std::endl;

    if (event_receiver.quitEvent()) {
        std::cout << "El cliente cerró la ventana." << std::endl;
    } else if (match.finished()) {
        std::cout << "La partida finalizó y el ganador es " << match.getWinner() << std::endl;
    }
    //Stops y joins de los hilos lanzados
    world.stop();
    snapshot_sender.stop();
    for (it2 = event_receiver.begin(); it2 = event_receiver.end(); it2++) {
        (*it2)->stop();
    }
    snapshots.push(NULL);
    snapshot_sender.join();
    world.join();
    for (it2 = event_receiver.begin(); it2 = event_receiver.end(); it2++) {
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