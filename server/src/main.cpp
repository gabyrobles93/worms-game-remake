#include <iostream>
#include "socket_error.h"
#include "server.h"

#define SRV_CONFIG_FILE_POS 1
#define SRV_PORT_POS 2

int main(int argc, char *argv[])
try {
    (void)argc;
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
}
