#ifndef SNAPSHOT_PUSHER_H
#define SNAPSHOT_PUSHER_H

#include "thread.h"
#include "World.h"
#include "blocking_queue.h"
#include <string>
#include "thread.h"

class SnapshotPusher : public Thread {
public:
    SnapshotPusher(World& world, BlockingQueue<YAML::Node>& models);
    ~SnapshotPusher();
    virtual void run(void);
    void stop();
private:
    bool keep_running;
    World& world;
    BlockingQueue<YAML::Node>& snapshots;
    //std::string snapshot;
    YAML::Node snapshot;
    virtual bool isRunning(void) const;
    virtual size_t getId(void) const;
};

#endif