#ifndef __SERVER_LOBBY_FEEDER_H__
#define __SERVER_LOBBY_FEEDER_H__

#include <mutex>
#include "server_protected_clients.h"
#include "thread.h"

class ServerLobbyFeeder : public Thread {
    private:
        ServerProtectedClients & clients;
        bool keep_running;
        bool feed_clients;
        std::mutex feed_mutex;

        bool isRunning(void) const;
        size_t getId(void) const;
    public:
        ServerLobbyFeeder(ServerProtectedClients &);
        ~ServerLobbyFeeder(void);
        void feedClients(void);
        void dontFeedClients(void);
        virtual void run(void);
        void stop(void);
};

#endif