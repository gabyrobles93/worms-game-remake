#ifndef __SERVER_PROTECTED_CLIENTS_H__
#define __SERVER_PROTECTED_CLIENTS_H__

#include <mutex>
#include <iostream>
#include <string>
#include <map>
#include "client.h"
#include "protocol.h"

class ServerProtectedClients {
    private:
        std::mutex clients_mutex;
        std::map<std::string,Client> clients;
    public:
        bool exists(std::string &);
        void addClient(std::string &, Protocol);
};

#endif