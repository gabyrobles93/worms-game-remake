#ifndef __SERVER_GAME_H__
#define __SERVER_GAME_H__

#include <vector>
#include "protocol.h"
#include "yaml.h"
#include "client.h"
#include "match.h"
#include "event_receiver.h"

class ServerGame {
    private:
        std::vector<Client*> clients;
        //std::map<size_t, Protocol*> protocols;
        //YAML::Node mapNode;
        std::string map_path;
        std::vector<EventReceiver*> event_receiver;
        void gameLoop(Match &, World &);
        void removePreviousTempFiles(void);
        void cleanClients(void);

    public:
        ServerGame(std::vector<Client*>, std::string &);
        ~ServerGame(void);
        void startGame(void);
};

#endif