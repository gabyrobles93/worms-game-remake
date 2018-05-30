#ifndef SNAPSHOT_SENDER_H
#define SNAPSHOT_SENDER_H

#include "thread.h"
#include <vector>
#include <string>
#include "protocol.h"
#include "blocking_queue.h"
#include "yaml.h"

class SnapshotSender : public Thread {
    private:
        Queue<YAML::Node> & snapshots;
        Protocol& protocol;
        bool keep_running;

        virtual bool isRunning(void) const;
        virtual size_t getId(void) const;
        
    public:
        SnapshotSender(Queue<YAML::Node> & snapshots, Protocol & protocol);
        ~SnapshotSender();
        virtual void run(void);
        void stop();
};

#endif
