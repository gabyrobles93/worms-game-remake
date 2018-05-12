#include <iostream>
#include <arpa/inet.h>
#include "protocol.h"
#include "socket.h"

Protocol::Protocol(SocketReadWrite socket) : skt(std::move(socket)) {
    std::cout << "Protocolo creado con socket conectado al servidor. " << this->skt.sockfd << std::endl;
}

void Protocol::getPlayerName(std::string & name) {
    uint32_t length;
    uchar playername[PLAYER_NAME_LENGTH_LIMIT];

    this->skt.getBuffer((uchar*)&length, 4);
    length = ntohl(length);

    this->skt.getBuffer(playername, length);
    std::string ret_name((char*) playername, (int)length);
    name = ret_name;    
}

void Protocol::sendName(std::string const & name) const {
    uint32_t length = name.size();
    length = htonl(length);
    this->skt.sendBuffer((const uchar*)&length, 4);
    this->skt.sendBuffer((const uchar*)name.c_str(), name.size());
}