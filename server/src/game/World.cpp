#include "World.h"
#include <iostream>

WorldPhysic World::_createWorldPhysic() {
    WorldPhysic worldPhysic;
    return worldPhysic;
}

World::World(YAML::Node& mapNode) : worldPhysic(_createWorldPhysic()){
    initializeWorld(mapNode);
}

World::~World() {
    for (std::map<int, Girder*>::iterator it = this->girders.begin(); it!= this->girders.end(); ++it) {
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
    //YAML::Node world_file = YAML::LoadFile("world.yml");
    //YAML::Node girders = world_file["girder"];
    //YAML::Node worms = world_file["worms"];

    YAML::Node static_node = mapNode["static"];
    this->dynamic_node = mapNode["dynamic"];

    YAML::Node short_girders_node = static_node["short_girders"];
    YAML::Node long_girders_node = static_node["long_girders"];

    YAML::Node worms_node = dynamic_node["worms"];

    for (YAML::iterator it = short_girders_node.begin(); it != short_girders_node.end(); ++it) {
        YAML::Node  short_girder = *it;
        int id = short_girder["id"].as<int>();
        float posX = (float) short_girder["x"].as<int>();
        float posY = (float) short_girder["y"].as<int>();
        float angle = (float) short_girder["angle"].as<int>();

        Girder* girder_ptr = new Girder(this->worldPhysic.getWorld(), posX, posY, angle, 0.8, 3);
        this->girders.insert(std::pair<int, Girder*>(id, girder_ptr));
    }

    for (YAML::iterator it = long_girders_node.begin(); it != long_girders_node.end(); ++it) {
        YAML::Node  long_girder = *it;
        int id = long_girder["id"].as<int>();
        float posX = (float) long_girder["x"].as<int>();
        float posY = (float) long_girder["y"].as<int>();
        float angle = (float) long_girder["angle"].as<int>();

        Girder* girder_ptr = new Girder(this->worldPhysic.getWorld(), posX, posY, angle, 0.8, 6);
        this->girders.insert(std::pair<int, Girder*>(id, girder_ptr));
    }

    for (YAML::iterator it = worms_node.begin(); it != worms_node.end(); ++it) {
        YAML::Node worm = *it;
        int id = worm["id"].as<int>();
        float posX = (float) worm["x"].as<int>();
        float posY = (float) worm["y"].as<int>();

        Worm* worm_ptr = new Worm(id, this->worldPhysic.getWorld(), posX, posY);
        this->worms.insert(std::pair<int, Worm*>(id, worm_ptr));
    }

    // for (YAML::iterator it = girders.begin(); it != girders.end(); ++it) {
    //     YAML::Node girder = *it;
    //     int id = girder["id"].as<int>();
    //     float posX = (float) girder["x"].as<int>();
    //     float posY = (float) girder["y"].as<int>();
    //     float angle = (float) girder["angle"].as<int>();
    //     float height = (float) girder["height"].as<int>();
    //     float width = (float) girder["width"].as<int>();
        
    //     Girder* girder_ptr = new Girder(this->worldPhysic.getWorld(), posX, posY, angle, height, width);
    //     this->girders.insert(std::pair<int, Girder*>(id, girder_ptr));
    // }


    //for (YAML::const_iterator it = worms.begin(); it != worms.end() ; ++it) {

    //}
}


std::map<int, Worm*> World::getWorms() {
    return this->worms;
}

std::map<int, Girder*> World::getGirders() {
    return this->girders;
}

// void World::update() {
//     int id = 1;
//     for (YAML::iterator it = worms.begin(); it != worms.end(); ++it) {
//         YAML::Node worm = *it;
//         worm[id]["x"] = worldPhysic.getPosX(id);
//         worm[id]["y"] = worldPhysic.getPosY(id);
//         id++;
//     }
// }

// void World::start() {
//     while (run) {
//         this->worldPhysic.step();
//         this->worldPhysic.clearForces();
//         //yamlUpdate();
//         //modelSend();
//         //MODEL SEND
//     }
// }

void World::run() {
    while (keep_running) {
        this->worldPhysic.step();
        this->worldPhysic.clearForces();
    }
}

//getModel() 

void World::moveLeft(size_t worm_id) {
    worms[worm_id]->moveLeft();
}

void World::moveRight(size_t worm_id) {
    worms[worm_id]->moveRight();
}

