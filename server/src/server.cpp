#include "server.h"
#include "socket.h"
#include "server_acceptor.h"
#include "../../client/src/protocol.h"

Server::Server(std::string & config_file_path,
 std::string & port) :
acceptor(port, clients),
feeder(clients)
{
    acceptor->start();
    feeder->start();
}

virtual void Server::run(void) {
    while (1) {
        try {

        } catch() {
            break;
        }

    }    
}
