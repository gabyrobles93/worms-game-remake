#ifndef __EVENT_RECEIVER_H__
#define __EVENT_RECEIVER_H__

#include "thread.h"
#include "event.h"
#include <SDL2/SDL.h>
#include "blocking_queue.h"
#include "client_configuration.h"
#include "camera.h"

class EventReceiver : public Thread {
    private:
        Queue<Event> & events;
        ClientConfiguration & cfg;    
        View::Camera & camera;
        bool keep_runing;
        virtual size_t getId(void) const;
        virtual bool isRunning(void) const;
    public:
        EventReceiver(Queue<Event> & events, ClientConfiguration & cfg, View::Camera & camera);
        ~EventReceiver(void);
        virtual void run(void);
        void stop(void);
};

#endif