#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <arpa/inet.h>
#include "protocol.h"
#include "socket.h"
#include "socket_error.h"
#include "protocol_error.h"

#define MSG_PROTOCOL_CLOSE_PEER "El servidor cerró el socket. "

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

void Protocol::sendFile(std::fstream & file) const {
    uint32_t length;

    file.seekg(0, std::ios::end);
    length = file.tellg();
    file.seekg(0, std::ios_base::beg);
    std::cout << "Voy a enviar archivo de longitud " << length << std::endl;
    uint32_t net_length = htonl(length);
    this->skt.sendBuffer((const uchar*)&net_length, 4);

    int remain = length;
    int readed = 0;
    uchar file_chop[FILE_TRANSFER_CHOP_SIZE];
    while (remain) {
        if (remain < FILE_TRANSFER_CHOP_SIZE) {
            file.read((char*)file_chop, remain);
            readed = remain;
        } else {
            file.read((char*)file_chop, FILE_TRANSFER_CHOP_SIZE);
            readed = FILE_TRANSFER_CHOP_SIZE;
        }
        remain -= readed;
        this->skt.sendBuffer(file_chop, readed);
    }
}

void Protocol::rcvFile(std::fstream & file) const {
    uint32_t length = 0;
    std::cout << "Esperando largo de archivo..." << std::endl;
    this->skt.getBuffer((uchar*)&length, 4);
    length = ntohl(length);
    std::cout << "Voy a recibir archivo de longitud " << length << std::endl;
    std::cout << "El largo del archivo son " << length << " bytes." << std::endl;

    if (length == 0) {
            std::stringstream msg;
            msg << MSG_PROTOCOL_CLOSE_PEER << std::strerror(errno);
            throw ProtocolError(msg.str());
    }

    int remain = length;
    int received = 0;
    uchar file_chop[FILE_TRANSFER_CHOP_SIZE];
    std::cout << "Esperando archivo..." << std::endl;
    while (remain) {
        std::cout << "Quiero recibir un archivo de " << remain << " bytes." << std::endl;
        if (remain < FILE_TRANSFER_CHOP_SIZE) {
            received = this->skt.getBuffer(file_chop, remain);
        } else {
            received = this->skt.getBuffer(file_chop, FILE_TRANSFER_CHOP_SIZE);
        }
        remain -= received;
        file.write((char*)file_chop, received);
    }
}

void Protocol::sendExitLobby(void) {
    this->skt.shutDown();
}