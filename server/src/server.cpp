#include <fstream>
#include <sstream>
#include "server.h"
#include "socket.h"
#include "socket_error.h"
#include "server_acceptor.h"
#include "protocol.h"
#include "server_error.h"

Server::Server(std::string & config_file_path,
 std::string & port) :
acceptor(port, clients),
feeder(clients)
{
    loadConfigFile(config_file_path);
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

void Server::loadConfigFile(std::string & config_file_path) {
    std::fstream cfg_file(config_file_path, std::ios::in);
    if (!cfg_file.is_open()) {
        std::stringstream msg;
        msg << MSG_CANT_OPEN_CFG_FILE << " " << config_file_path;
        throw ServerError(msg.str());
    }
}

 bool Server::isRunning(void) const {
     return true;
 }

Server::~Server(void) {
    // Cerrar server ordenadamente
}

size_t  Server::getId(void) const{
    return 0;
}

void Server::stop(void) {
    // Stopear servidor.
    // Seguramente haya que cerrar los sockets ordenadamente. 
}