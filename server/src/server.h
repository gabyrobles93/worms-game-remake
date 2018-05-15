#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include "thread.h"
#include "../../client/src/protocol.h"
#include "server_acceptor.h"
#include "server_protected_clients.h"
#include "server_lobby_feeder.h"
#include "socket.h"
#include "client.h"

class Server : public Thread {
    private:
        ServerAcceptor acceptor;
        ServerLobbyFeeder feeder;
        ServerProtectedClients clients;

        bool isRunning(void) const;
        size_t getId(void) const;
    public:
        void stop(void);
        Server(std::string & cfile, std::string & port);
        virtual void run(void);
        ~Server(void);
};

#endif