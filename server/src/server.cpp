#include "server.h"
#include "socket.h"
#include "socket_error.h"
#include "server_acceptor.h"
#include "../../client/src/protocol.h"

Server::Server(std::string & config_file_path,
 std::string & port) :
acceptor(port, clients),
feeder(clients)
{
    this->acceptor.start();
    this->feeder.start();
}

void Server::run(void) {
    while (1) {
        try {

        } catch(const SocketError & e) {
            break;
        }

    }    
}
