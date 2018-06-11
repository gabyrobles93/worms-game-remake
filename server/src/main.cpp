#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <unistd.h>
#include "yaml.h"
#include "socket.h"
#include "socket_error.h"
#include "protocol.h"
#include "protocol_error.h"
#include "types.h"
#include "World.h"
#include "snapshot_sender.h"
#include "blocking_queue.h"
#include "event.h"
#include "match.h"
#include "event_receiver.h"
#include "Configuration.h"
#include "snapshot.h"
#include "server.h"
#include "server_error.h"

#define SRV_ARGS_QTY 3
#define SRV_CONFIG_FILE_POS 1
#define SRV_PORT_POS 2
#define MAP_PATH "../maps/el_mapa_1.yml"
#define MAX_QUEUE_SNAPSHOTS 256

Configuration gConfiguration;

int main(int argc, char *argv[]) try {
     if (argc < SRV_ARGS_QTY) {
        std::cout << "Servidor mal invocado." << std::endl;
        std::cout << "Forma de uso: './server <config_file_path> <port>" << std::endl;
        return 0;
    }
    std::string config_file_path(argv[SRV_CONFIG_FILE_POS]);
    std::string port(argv[SRV_PORT_POS]);
    Server server(config_file_path, port);

    server.start();

    char c;
    do {
        c = getchar();
    } while (c != 'q');

    server.stop();
    server.join();

    return 0;

} catch(const SocketError & e) {
    std::cout << e.what() << std::endl;
} catch(const ServerError & s) {
    std::cout << s.what() << std::endl;
} catch(const ProtocolError & p) {
    std::cout << p.what() << std::endl;
} catch(const std::exception & g) {
    std::cout << g.what() << std::endl;
}
