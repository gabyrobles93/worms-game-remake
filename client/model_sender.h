#ifndef __MODEL_SENDER_H__
#define __MODEL_SENDER_H__

#include "thread.h"
#include "protocol.h"
#include "blocking_queue.h"

class ModelSender : public Thread {
    private:
        Protocol & protocol;
        BlockingQueue<char> & queue;
    public:
        ModelSender(Protocol &, BlockingQueue<char> &);
};

#endif