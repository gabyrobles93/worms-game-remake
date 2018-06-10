#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "protocol.h"
#include "yaml.h"
#include "types.h"
#include <string>
#include <vector>

class Client {
    private:
        Protocol protocol;
        std::string player_name;
        client_status_t status;
        std::string joined_match_creator_name;

    public:
        Client(Protocol, std::string &);
        void sendGamesStatus(YAML::Node);
        Event rcvEvent(void);
        std::string getPlayerName(void);
        void setStatus(client_status_t);
        client_status_t getStatus(void);
        void sendResponse(int, std::string &);
        void sendGameStart(int, std::string &, std::string &);
        void setJoinedMatchGameCreator(std::string &);
        void clearJoinedMatchGameCreator(void);
        std::string getJoinedMatchCreatorName(void);
        void sendWaitingPlayers(std::vector<std::string>);
};

#endif