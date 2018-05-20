#ifndef __CLIENT_HANLDER_H__
#define __CLIENT_HANLDER_H__

#include "thread.h"
#include "World.h"
#include "protocol.h"

class ClientHandler : public Thread {
    private:
        Protocol protocol;
        World& world;
        bool keep_running;
        size_t team_id;
        // Game Status
        virtual bool isRunning(void) const;
        virtual size_t getId(void) const;
    public:
        ClientHandler(SocketReadWrite skt, World& w);
        ~ClientHandler(void);
        virtual void run(void);
};

#endif