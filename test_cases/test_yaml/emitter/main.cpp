#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <string>
#include "include/yaml-cpp/yaml.h"

typedef unsigned char uchar;

#define LISTENING_PORT "8080"

typedef unsigned char uchar;

int main() {
    YAML::Node node_map = YAML::LoadFile("../map.yml");
    //YAML::Node node_worms = node_map["dynamic"]["worms"];

    std::stringstream str1;
    str1 << node_map;
    std::cout << str1.str() << std::endl;

    std::cout << "***********************" << std::endl;

    YAML::Node::iterator it;

    for (it = node_map["dynamic"]["worms"].begin(); it != node_map["dynamic"]["worms"].end(); it++) {
        (*it)["x"] = "30";
    }

    std::cout << "***********************" << std::endl;

    std::stringstream str;

    str << node_map;

    std::cout << str.str() << std::endl;


    return 0;
}