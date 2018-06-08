#include "snapshot.h"
#include "snapshot_sender.h"
#include "socket_error.h"
#include <iostream>

SnapshotSender::SnapshotSender(Queue<Snapshot> & snapshots, Match & m, Protocol& protocol) : 
snapshots(snapshots) ,
match(m),
protocol(protocol) {
    this->keep_running = true;
}

SnapshotSender::~SnapshotSender() {
}

void SnapshotSender::run() {
    while (keep_running) {
        Snapshot snapshot(this->snapshots.pop());
        // agregar nodo de game status.
        snapshot.updateGameStatus(this->match);
        YAML::Node nodeSnapshot = snapshot.getSnapshot();
        // std::stringstream ss;
        // ss << nodeSnapshot["projectiles"] << std::endl;
        // std::cout << ss.str() << std::endl;
        this->protocol.sendModel(nodeSnapshot);
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