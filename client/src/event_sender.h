#ifndef __EVENT_SENDER_H__
#define __EVENT_SENDER_H__

#include "thread.h"
#include "protocol.h"
#include "blocking_queue.h"
#include "socket.h"
#include "types.h"

class EventSender : public Thread {
    private:
        Protocol & protocol;
        BlockingQueue<action_t> & events;
        bool keep_runing;
    
        virtual bool isRunning(void) const;
        virtual size_t getId(void) const;
    public:
        EventSender(Protocol &, BlockingQueue<action_t> &);
        ~EventSender(void);
        virtual void run(void);
        void stop(void);
};

#endif