#include "snapshot.h"
#include "snapshot_sender.h"
#include "socket_error.h"
#include <iostream>
#include <unistd.h>
#include "client.h"

SnapshotSender::SnapshotSender(Queue<Snapshot*> & snapshots, Match & m, std::vector<Client*> cl) : 
snapshots(snapshots) ,
match(m),
clients(cl) {
    this->keep_running = true;
}

SnapshotSender::~SnapshotSender() {
}

void SnapshotSender::run() {
    while (keep_running) {
        usleep(16666);
        Snapshot* snapshot = this->snapshots.pop();
        if (keep_running && snapshot) {
            sendSnapshot(snapshot);
        }
    //std::cout << snapshot->getSnapshot() << std::endl;
    }
    std::cout << "Sacando la ultima foto con partida finished." << std::endl;
    Snapshot* snapshot = this->snapshots.pop();
    sendLastSnapshot(snapshot);
}

void SnapshotSender::sendSnapshot(Snapshot * snapshot) {
    snapshot->updateGameStatus(this->match);
    std::stringstream ss;
    ss << snapshot->getSnapshot();
    //std::cout << ss.str() << std::endl;
    std::vector<Client*>::const_iterator it;
    for (it = this->clients.begin(); it != this->clients.end(); it++) {
        (*it)->sendSnapShot(ss);
    }
    
    delete snapshot;   
}

void SnapshotSender::sendLastSnapshot(Snapshot * last_snapshot) {
    last_snapshot->updateGameStatusLastSnapshot(this->match);
    std::stringstream ss;
    ss << last_snapshot->getSnapshot();
    std::cout << ss.str() << std::endl;
    std::vector<Client*>::const_iterator it;
    for (it = this->clients.begin(); it != this->clients.end(); it++) {
        std::cout << "Enviando ultima snapshot a cliente." << std::endl;
        (*it)->sendSnapShot(ss);
    }
    
    delete last_snapshot;  
}

size_t SnapshotSender::getId(void) const{
    return 0;
}

bool SnapshotSender::isRunning(void) const {
    return this->keep_running;
}

void SnapshotSender::stop() {
    this->keep_running = false;
}
