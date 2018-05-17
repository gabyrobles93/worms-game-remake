#include <iostream>
#include <fstream>
#include <unistd.h>
#include "socket.h"
#include "socket_error.h"
#include "protocol.h"
#include "protocol_error.h"
#include "thread.h"
#include "blocking_queue.h"
#include "yaml.h"

#define CONNECTION_HOST "localhost"
#define CONNECTION_PORT "8080"

int main(int argc, char *argv[])
try {
    SocketConnection skt(CONNECTION_HOST, CONNECTION_PORT);
    Protocol protocol(std::move(skt));
    YAML::Node model;
    BlockingQueue<char> events;

    

    char c;
    do {
        c = getchar();
        events.push(c);
    } while (c != 'q');


} catch(const SocketError & e) {
    std::cout << e.what() << std::endl;
}
