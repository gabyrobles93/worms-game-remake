#include "SnapshotSender.h"
#include "socket_error.h"
#include <iostream>

SnapshotSender::SnapshotSender(BlockingQueue<YAML::Node>& snapshots, Protocol& protocol) : 
snapshots(snapshots) , 
/*clients(clients)*/
protocol(protocol) {
    this->keep_running = true;
}

SnapshotSender::~SnapshotSender() {
}

void SnapshotSender::run() {
    while (keep_running) {
        YAML::Node snapshot = this->snapshots.pop();
        try {
            this->protocol.sendModel(snapshot);
        } catch(const SocketError & e) {
            return;
        }
        //for (std::vector<Protocol*>::iterator it = clients.begin(); it != clients.end(); ++it ){
            //TODO *it.send(snapshot);
        //} 
    }
}

size_t SnapshotSender::getId(void) const{
    return 0;
}

bool SnapshotSender::isRunning(void) const {
    return true;
}

void SnapshotSender::stop() {
    this->keep_running = false;
}