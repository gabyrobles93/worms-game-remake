#include "World.h"
#include <unistd.h>
#include <iostream>

World::World(std::string & map_path) {
    this->node_map = YAML::LoadFile(map_path);
    initializeWorld();
    this->keep_running = true;
}

World::~World() {
    for (std::map<int, Girder*>::iterator it = this->girders.begin(); it!= this->girders.end(); ++it) {
        delete it->second;
    }

    for (std::map<int, Worm*>::iterator it = this->worms.begin(); it != this->worms.end(); ++it) {
        delete it->second;
    }
}

size_t World::getId(void) const {
    return 0;
}

bool World::isRunning(void) const {
    return true;
}

void World::initializeWorld() {
    std::cout << "Inicializando mundo" << std::endl;
    const YAML::Node& static_node = this->node_map["static"];
    const YAML::Node& dynamic_node = this->node_map["dynamic"];

    const YAML::Node & short_girders_node = static_node["short_girders"];
    const YAML::Node & long_girders_node = static_node["long_girders"];

    const YAML::Node& worms_node = dynamic_node["worms"];

    for (YAML::const_iterator it = short_girders_node.begin(); it != short_girders_node.end(); ++it) {
        const YAML::Node &  short_girder = *it;
        int id = short_girder["id"].as<int>();
        float posX = (float) short_girder["x"].as<int>() * SCALING_FACTOR;
        float posY = (float) short_girder["y"].as<int>() * SCALING_FACTOR;
        float angle = (float) short_girder["angle"].as<int>() * GRADTORAD;

        Girder* girder_ptr = new Girder(this->worldPhysic.getWorld(), posX, posY, angle, 0.8, 3);
        this->girders.insert(std::pair<int, Girder*>(id, girder_ptr));
    }

    for (YAML::const_iterator it = long_girders_node.begin(); it != long_girders_node.end(); ++it) {
        const YAML::Node&  long_girder = *it;
        int id = long_girder["id"].as<int>();
        float posX = (float) long_girder["x"].as<int>() * SCALING_FACTOR;
        float posY = (float) long_girder["y"].as<int>() * SCALING_FACTOR;
        float angle = (float) long_girder["angle"].as<int>() * GRADTORAD;

        Girder* girder_ptr = new Girder(this->worldPhysic.getWorld(), posX, posY, angle, 0.8, 6);
        this->girders.insert(std::pair<int, Girder*>(id, girder_ptr));
    }

    int id;
    float x;
    float y;
    for (YAML::const_iterator it = worms_node.begin(); it != worms_node.end(); it++) {
        const YAML::Node& worm = *it;
        id = worm["id"].as<int>();
        x = (float) worm["x"].as<int>() * SCALING_FACTOR;
        y = (float) worm["y"].as<int>() * SCALING_FACTOR;
        Worm * new_worm = new Worm(id, this->worldPhysic.getWorld(), x, y);
        this->worms.insert(std::pair<int, Worm*>(id, new_worm));
    }
}


std::map<int, Worm*> World::getWorms() {
    return this->worms;
}

std::map<int, Girder*> World::getGirders() {
    return this->girders;
}

void World::updateYAML() {
    YAML::Node::iterator it;
    std::string x;
    std::string y;
    for (it = this->node_map["dynamic"]["worms"].begin(); it !=this->node_map["dynamic"]["worms"].end(); it++) {
        x = std::to_string((int) (this->worms[(*it)["id"].as<int>()]->getPosX() / SCALING_FACTOR));
        y = std::to_string((int) (this->worms[(*it)["id"].as<int>()]->getPosY() / SCALING_FACTOR));
        (*it)["x"] = x;
        (*it)["y"] = y;
/*      std::cout << "x: " << x << std::endl;
        std::cout << "y: " << y << std::endl; */
    }
}

void World::run() {
    while (this->keep_running) {
        usleep(100);
        this->worldPhysic.step();
        this->worldPhysic.clearForces();
        updateYAML();
    }
}

YAML::Node World::getSnapshot() {
    return this->node_map["dynamic"];
}

void World::moveLeft(size_t worm_id) {
    worms[worm_id]->moveLeft();
}

void World::moveRight(size_t worm_id) {
    worms[worm_id]->moveRight();
}

void World::stop() {
    this->keep_running = false;
}
