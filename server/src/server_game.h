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
        YAML::Node mapNode;

        void gameLoop(Match &, World &);

    public:
        ServerGame(std::vector<Client*>, std::string &);
        void startGame(void);
};

#endif