#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include "thread.h"
#include "protocol.h"
#include "server_acceptor.h"
#include "server_protected_clients.h"
#include "server_lobby_feeder.h"
#include "socket.h"
#include "client.h"

#define MSG_CANT_OPEN_CFG_FILE "No se pudo abrir el archivo de configuracion."

class Server : public Thread {
    private:
        ServerAcceptor acceptor;
        ServerProtectedClients clients;
        bool keep_running;

        bool isRunning(void) const;
        size_t getId(void) const;
        void loadConfigFile(std::string &);
        std::string findFreeName(std::string &) const;
        
    public:
        void stop(void);
        Server(std::string & cfile, std::string & port);
        virtual void run(void);
        ~Server(void);
};

#endif