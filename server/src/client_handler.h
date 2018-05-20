#ifndef __CLIENT_HANLDER_H__
#define __CLIENT_HANLDER_H__

#include "thread.h"
#include "World.h"
#include "protocol.h"

class ClientHandler : public Thread {
    private:
        World & world;
        Protocol protocol;
        bool keep_runing;
        size_t team_name;
        // Game Status
        virtual bool isRunning(void) const;
        virtual size_t getId(void) const;
    public:
        ClientHandler(SocketReadWrite, World &);
        ~ClientHandler(void);
        virtual void run(void);
};

#endif