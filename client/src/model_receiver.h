#ifndef _MODEL_RECEIVER_H__
#define _MODEL_RECEIVER_H__

#include "thread.h"
#include "protocol.h"
#include "blocking_queue.h"

class ModelReceiver : public Thread {
    private:
        Protocol & protocol;
        Model & model;
        bool keep_runing;

        virtual bool isRunning(void) const;
        virtual size_t getId(void) const;
    public:
        ModelReceiver(Protocol &, Model &);
        ~ModelReceiver(void);
        virtual void run(void);
        void stop(void);
};

#endif