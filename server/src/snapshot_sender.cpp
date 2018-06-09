#include "snapshot.h"
#include "snapshot_sender.h"
#include "socket_error.h"
#include <iostream>
#include <unistd.h>

SnapshotSender::SnapshotSender(Queue<Snapshot*> & snapshots, Match & m, Protocol& protocol) : 
snapshots(snapshots) ,
match(m),
protocol(protocol) {
    this->keep_running = true;
}

SnapshotSender::~SnapshotSender() {
}

void SnapshotSender::run() {
    while (keep_running) {
        usleep(16666);
        Snapshot* snapshot = this->snapshots.pop();
        // agregar nodo de game status.
        snapshot->updateGameStatus(this->match);
        
        //YAML::Node nodeSnapshot = snapshot->getSnapshot();
        
        //std::cout << snapshot->getSnapshotCString() << std::endl;
        //std::string text_node(snapshot->getSnapshotCString());
        //YAML::Node test = YAML::Load(text_node);
        //YAML::Node nodeSnap = YAML::Load(text_node);
        std::stringstream ss;
        ss << snapshot->getSnapshot();
        //ss << nodeSnap << std::endl;
        //std::cout << ss.str() << std::endl;
        //this->protocol.sendModel(nodeSnap);
        this->protocol.sendGameMapAsString(ss);
        delete snapshot;
    }
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