#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include "include/yaml-cpp/yaml.h"
#include "socket.h"

typedef unsigned char uchar;

#define LISTENING_PORT "8080"

int main(int argc, char *argv[]) {
    SocketListener skt(LISTENING_PORT);
    SocketReadWrite sktrw = skt.accept_connection();

    YAML::Node node = YAML::LoadFile("games.yml");
    uint32_t node_size = sizeof(node);
    std::stringstream serialized;
    serialized << node;
    std::cout << serialized.str() << std::endl;
    uint32_t leng = serialized.str().length();
    std::cout << "len: " << leng << std::endl;
    sktrw.sendBuffer((const uchar *) &leng, 4);
    sktrw.sendBuffer((const uchar *) serialized.str().c_str(), leng);

    return 0;
}