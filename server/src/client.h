#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "protocol.h"

typedef enum {
    lobby,
    joined,
    creator
} client_status_t;

class Client {
    private:
        Protocol protocol;
        client_status_t status;
    public:
        Client(Protocol);
};

#endif