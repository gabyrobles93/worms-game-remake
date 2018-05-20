#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <string>
#include "socket.h"
#include "yaml.h"
#include "types.h"

#define PLAYER_NAME_LENGTH_LIMIT 20
#define FILENAME_LENGTH_LIMIT 255
#define FILE_TRANSFER_CHOP_SIZE 255


class Protocol {
    private:
        SocketReadWrite skt;

    public:
        explicit Protocol(SocketReadWrite);
        void getPlayerName(std::string &);
        void sendName(std::string const &) const;
        void rcvFile(std::fstream & file) const;
        void sendFile(std::fstream & file) const;
        void sendExitLobby(void);
        void rcvGameMap(YAML::Node &);
        void sendGameMap(YAML::Node &);
        void sendEvent(action_t);
        void rcvEvent(action_t);
        void sendModel(YAML::Node &);
        void rcvModel(YAML::Node &);
};

#endif