#ifndef __SERVER_LOBBY_FEEDER_H__
#define __SERVER_LOBBY_FEEDER_H__

#include "server_protected_clients.h"
#include "thread.h"

class ServerLobbyFeeder : public Thread {
    private:
        ServerProtectedClients & clients;

        bool isRunning(void) const;
        size_t getId(void) const;
    public:
        ServerLobbyFeeder(ServerProtectedClients &);
        virtual void run(void);
        void stop(void);
};

#endif