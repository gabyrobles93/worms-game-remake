#include <iostream>
#include "protocol.h"
#include "socket.h"

Protocol::Protocol(SocketReadWrite socket) : skt(std::move(socket)) {
    std::cout << "Protocolo creado con socket conectado al servidor. " << this->skt.sockfd << std::endl;
}