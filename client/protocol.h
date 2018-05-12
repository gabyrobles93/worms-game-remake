#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <string>
#include "socket.h"

#define PLAYER_NAME_LENGTH_LIMIT 20

class Protocol {
    private:
        SocketReadWrite skt;
    public:
        explicit Protocol(SocketReadWrite);
        void getPlayerName(std::string &);
        void sendName(std::string const &) const;
};

#endif