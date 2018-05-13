#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include "thread.h"
#include "../../client/src/protocol.h"
#include "server_lobby.h"
#include "socket.h"

class Server : public Thread {
    private:
        ProtectedLobbyStatus lobby_status;
        SocketListener skt_listener;
        ServerLobby server_lobby;
        std::map<std::string, Protocol> clients_in_lobby;
        size_t clients_in_lobby_counter;
        size_t clients_in_game_counter;

        bool isRunning(void) const;
        size_t getId(void) const;
        std::string findFreeName(std::string &) const;
    public:
        void stop(void);
        Server(std::string &, std::string &);
        virtual void run(void);
        ~Server(void);
};

#endif