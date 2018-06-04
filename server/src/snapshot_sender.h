#ifndef SNAPSHOT_SENDER_H
#define SNAPSHOT_SENDER_H

#include "snapshot.h"
#include "thread.h"
#include <vector>
#include <string>
#include "protocol.h"
#include "blocking_queue.h"
#include "yaml.h"
#include "match.h"

class SnapshotSender : public Thread {
    private:
        Queue<Snapshot> & snapshots;
        Match & match;
        Protocol& protocol;
        bool keep_running;

        virtual bool isRunning(void) const;
        virtual size_t getId(void) const;
        
    public:
        SnapshotSender(Queue<Snapshot> & snapshots, Match &, Protocol & protocol);
        ~SnapshotSender();
        virtual void run(void);
        void stop();
};

#endif
