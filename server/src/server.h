#ifndef __SERVER_H__
#define __SERVER_H__
#include <string>
#include <map>
#include "thread.h"
#include "protocol.h"
#include "socket.h"
#include "client.h"
#include "lobby_attendant.h"
#include "waiting_game.h"
#include "protected_waiting_games.h"

#define MSG_CANT_OPEN_CFG_FILE "No se pudo abrir el archivo de configuracion."

class Server : public Thread {
    private:
        SocketListener skt;
        std::map<std::string, Client*> clients;
        std::map<std::string, LobbyAttendant*> clients_in_lobby;
        ProtectedWaitingGames protected_waiting_games;
        std::map<std::string, WaitingGame*> waiting_games;
        bool keep_running;

        bool isRunning(void) const;
        size_t getId(void) const;
        std::string findFreeName(std::string &);
        void cleanLobby(void);
        void cleanQuitedClients(void);
    public:
        void stop(void);
        Server(std::string & port);
        virtual void run(void);
        ~Server(void);
};

#endif