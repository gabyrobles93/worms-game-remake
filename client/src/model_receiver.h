#ifndef _MODEL_RECEIVER_H__
#define _MODEL_RECEIVER_H__

#include "thread.h"
#include "protocol.h"
#include "blocking_queue.h"

class ModelReceiver : public Thread {
    private:
        Protocol & protocol;
        YAML::Node & model;
        bool keep_runing;

        virtual bool isRunning(void) const;
        virtual size_t getId(void) const;
    public:
        ModelReceiver(Protocol &, YAML::Node &);
        ~ModelReceiver(void);
        virtual void run(void);
        void stop(void);
};

#endif