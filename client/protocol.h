#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "socket.h"

class Protocol {
    private:
        SocketReadWrite skt;
    public:
        explicit Protocol(SocketReadWrite);
};

#endif