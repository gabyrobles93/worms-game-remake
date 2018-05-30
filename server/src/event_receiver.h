#ifndef __EVENT_RECEIVER_H__
#define __EVENT_RECEIVER_H__

#include "thread.h"
#include "World.h"
#include "protocol.h"
#include "match.h"

class EventReceiver : public Thread {
    private:
        Protocol & protocol;
        World & world;
        Match & match;
        size_t team_id;
        bool keep_running;
        bool quit_event; 
        
        virtual bool isRunning(void) const;
        virtual size_t getId(void) const;

    public:
        EventReceiver(Protocol &, World &, Match &, size_t);
        virtual void run(void);
        void stop(void);
        bool quitEvent(void);
};

#endif