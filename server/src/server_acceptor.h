#ifndef __SERVER_ACCEPTOR_H__
#define __SERVER_ACCEPTOR_H__

#include <string>
#include "server_protected_clients.h"
#include "thread.h"

class ServerAcceptor : public Thread {
    private:
        SocketListener skt;
        ServerProtectedClients & clients;
        bool isRunning(void) const;
        size_t getId(void) const;
        std::string findFreeName(std::string &) const;
    public:
        ServerAcceptor(std::string & port, ServerProtectedClients & clients);
        void stop(void);
        virtual void run(void);
};

#endif