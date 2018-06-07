#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "protocol.h"
#include "yaml.h"
#include "types.h"

class Client {
    private:
        Protocol protocol;
        std::string player_name;
        client_status_t status;
    public:
        Client(Protocol, std::string &);
        void sendGamesStatus(YAML::Node);
        Event rcvEvent(void);
        std::string getPlayerName(void);
        void setStatus(client_status_t);
        client_status_t getStatus(void);
};

#endif