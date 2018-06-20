#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
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

#define MIN_SRV_ARGS_QTY 2
#define MAX_SRV_ARGS_QTY 3
#define SRV_CONFIG_FILE_POS 2
#define SRV_PORT_POS 1

Configuration gConfiguration;

int main(int argc, char *argv[]) try {
     if (argc < MIN_SRV_ARGS_QTY || argc > MAX_SRV_ARGS_QTY) {
        std::cout << "Servidor mal invocado." << std::endl;
        std::cout << "Forma de uso: './server <port> [config-file-path]" << std::endl;
        return 0;
    } else if (argc == MAX_SRV_ARGS_QTY) {
        try {
            YAML::Node config_node = YAML::LoadFile(argv[SRV_CONFIG_FILE_POS]);
            gConfiguration.loadConfigFile(config_node);
        } catch (const YAML::Exception & err) {
            std::cout << "No se pudo abrir el archivo de configuración espcificado. Se usarán valores de configuración por defecto: " << err.what() << std::endl;
        }
    } else {
        std::cout << "No se cargó archivo de configuración, se utilizarán valores por defecto." << std::endl;
    }

    std::string port(argv[SRV_PORT_POS]);
    Server server(port);

    server.start();

    char c;
    do {
        c = getchar();
    } while (c != 'q');

    std::cout << "Servidor detenido." << std::endl;
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
