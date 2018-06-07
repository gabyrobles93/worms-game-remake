#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include <map>
#include "thread.h"
#include "protocol.h"
#include "protected_matchs_status.h"
#include "socket.h"
#include "client.h"
#include "lobby_attendant.h"

#define MSG_CANT_OPEN_CFG_FILE "No se pudo abrir el archivo de configuracion."

class Server : public Thread {
    private:
        SocketListener skt;
        ProtectedMatchsStatus game_status;
        std::map<std::string, Client*> clients;
        std::map<std::string, LobbyAttendant*> clients_in_lobby;
        bool keep_running;

        bool isRunning(void) const;
        size_t getId(void) const;
        void loadConfigFile(std::string &);
        std::string findFreeName(std::string &);
        void cleanFinishedClients(void);
    public:
        void stop(void);
        Server(std::string & cfile, std::string & port);
        virtual void run(void);
        ~Server(void);
};

#endif