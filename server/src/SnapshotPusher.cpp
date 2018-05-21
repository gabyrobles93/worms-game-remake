#include "SnapshotPusher.h"

SnapshotPusher::SnapshotPusher(World& world, BlockingQueue<YAML::Node>& snapshots) : 
world(world) , 
snapshots(snapshots)  {
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
        snapshots.push(this->snapshot);
    }
}