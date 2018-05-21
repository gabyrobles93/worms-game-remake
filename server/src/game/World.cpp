#include "World.h"
#include <iostream>

World::World(YAML::Node& mapNode) {
    initializeWorld(mapNode);
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

void World::initializeWorld(YAML::Node& mapNode) {
    std::cout << "Inicializando mundo" << std::endl;
    YAML::Node static_node = mapNode["static"];
    this->dynamic_node = mapNode["dynamic"];

    YAML::Node short_girders_node = static_node["short_girders"];
    YAML::Node long_girders_node = static_node["long_girders"];

    YAML::Node worms_node = dynamic_node["worms"];

    for (YAML::iterator it = short_girders_node.begin(); it != short_girders_node.end(); ++it) {
        YAML::Node  short_girder = *it;
        int id = short_girder["id"].as<int>();
        float posX = (float) short_girder["x"].as<int>() * SCALING_FACTOR;
        float posY = (float) short_girder["y"].as<int>() * SCALING_FACTOR;
        float angle = (float) short_girder["angle"].as<int>() * GRADTORAD;

        Girder* girder_ptr = new Girder(this->worldPhysic.getWorld(), posX, posY, angle, 0.8, 3);
        this->girders.insert(std::pair<int, Girder*>(id, girder_ptr));
    }

    for (YAML::iterator it = long_girders_node.begin(); it != long_girders_node.end(); ++it) {
        YAML::Node  long_girder = *it;
        int id = long_girder["id"].as<int>();
        float posX = (float) long_girder["x"].as<int>() * SCALING_FACTOR;
        float posY = (float) long_girder["y"].as<int>() * SCALING_FACTOR;
        float angle = (float) long_girder["angle"].as<int>() * GRADTORAD;

        Girder* girder_ptr = new Girder(this->worldPhysic.getWorld(), posX, posY, angle, 0.8, 6);
        this->girders.insert(std::pair<int, Girder*>(id, girder_ptr));
    }

    for (YAML::iterator it = worms_node.begin(); it != worms_node.end(); ++it) {
        YAML::Node worm = *it;
        int id = worm["id"].as<int>();
        float posX = (float) worm["x"].as<int>() * SCALING_FACTOR;
        float posY = (float) worm["y"].as<int>() * SCALING_FACTOR;

        Worm* worm_ptr = new Worm(id, this->worldPhysic.getWorld(), posX, posY);
        this->worms.insert(std::pair<int, Worm*>(id, worm_ptr));
    }
}


std::map<int, Worm*> World::getWorms() {
    return this->worms;
}

std::map<int, Girder*> World::getGirders() {
    return this->girders;
}

void World::updateWorld() {
    std::map<int, Worm*>::iterator it;
    for (it = this->worms.begin(); it != this->worms.end(); it++) {
       int id = it->first;
       this->dynamic_node["worms"][id] = worms[id]->getPosX();
       this->dynamic_node["worms"][id] = worms[id]->getPosY();
    }
}

void World::run() {
    while (keep_running) {
        std::cout << "CORRIENDO MUNDO" << std::endl;
        //this->worldPhysic.step();
        //this->worldPhysic.clearForces();
        //updateWorld();
    }
    std::cout << "TERMINAR DE CORRER MUndo" << std::endl;
}

// std::string World::getModel() {
//     std::stringstream node_stream;
//     node_stream << this->dynamic_node;
//     return node_stream.str();
// }

YAML::Node World::getSnapshot() {
    return this->dynamic_node;
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
