#include "SnapshotPusher.h"
#include <iostream>

SnapshotPusher::SnapshotPusher(World& world, BlockingQueue<YAML::Node>& snapshots) : 
world(world) , 
snapshots(snapshots)  {
    this->keep_running = true;
}

SnapshotPusher::~SnapshotPusher(){

}

bool SnapshotPusher::isRunning(void) const {
    return true;
}

size_t SnapshotPusher::getId(void) const {
    return 0;
}

void SnapshotPusher::run() {
    while (keep_running) {
        this->snapshot = this->world.getSnapshot();
        //std::cout << "Voy a pushear \n";
        snapshots.push(this->snapshot);
        //std::cout << "Pushie\n" << std::endl;
    }
}

void SnapshotPusher::stop() {
    this->keep_running = false;
}