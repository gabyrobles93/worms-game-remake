#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "protocol.h"
#include "yaml.h"

typedef enum {
    lobby,
    joined,
    creator,
    on_match
} client_status_t;

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

};

#endif