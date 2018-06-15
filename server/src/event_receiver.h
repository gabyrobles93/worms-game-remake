#ifndef __EVENT_RECEIVER_H__
#define __EVENT_RECEIVER_H__

#include "thread.h"
#include "World.h"
#include "client.h"
#include "match.h"

class EventReceiver : public Thread {
    private:
        Client * client;
        World & world;
        Match & match;
        size_t team_id;
        bool keep_running;
        bool quit_event; 
        
    public:
        EventReceiver(Client *, World &, Match &, size_t);
        virtual void run(void);
        void stop(void);
        bool quitEvent(void);
        virtual bool isRunning(void) const;
        virtual size_t getId(void) const;
};

#endif