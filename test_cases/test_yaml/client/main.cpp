#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <string>
#include "include/yaml-cpp/yaml.h"
#include "socket.h"

typedef unsigned char uchar;

#define LISTENING_PORT "8080"

typedef unsigned char uchar;

int main(int argc, char *argv[]) {
    SocketConnection skt("localhost", "8080");

    YAML::Node nodito;

    uint32_t node_size;
    skt.getBuffer((uchar *) &node_size, 4);
    std::cout << "len: " << node_size << std::endl;
    uchar * node = new uchar[node_size];
    skt.getBuffer((uchar *) node, node_size);

    std::string texto((char*)node);

    nodito =  YAML::Load(texto);

    std::stringstream serialized;
    serialized << nodito;
    std::cout << serialized.str() << std::endl;

    const YAML::Node& nod = nodito["games"];

   for (YAML::const_iterator it = nod.begin(); it != nod.end(); ++it) {
        const YAML::Node& game = *it;
        std::string game_name = game["name"].as<std::string>();
        std::string game_creator = game["creator"].as<std::string>();
        std::string game_players = game["players"].as<std::string>();
        game_players += "/3";

        std::cout << game_name << std::endl;
        std::cout << game_creator << std::endl;
        std::cout << game_players << std::endl;
   }

    return 0;
}