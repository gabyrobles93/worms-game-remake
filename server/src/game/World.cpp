#include "World.h"
#include <iostream>

WorldPhysic World::_createWorldPhysic() {
    WorldPhysic worldPhysic;
    return worldPhysic;
}

World::World() : worldPhysic(_createWorldPhysic()){
    initializeWorld();
}

World::~World() {
    for (std::map<int, Girder*>::iterator it = this->girders.begin(); it!= this->girders.end(); ++it) {
        delete it->second;
    }
}

void World::initializeWorld() {
    YAML::Node world_file = YAML::LoadFile("world.yml");
    YAML::Node girders = world_file["girder"];
    YAML::Node worms = world_file["worms"];

    for (YAML::iterator it = girders.begin(); it != girders.end(); ++it) {
        YAML::Node girder = *it;
        int id = girder["id"].as<int>();
        float posX = (float) girder["x"].as<int>();
        float posY = (float) girder["y"].as<int>();
        float angle = (float) girder["angle"].as<int>();
        float height = (float) girder["height"].as<int>();
        float width = (float) girder["width"].as<int>();
        
        Girder* girder_ptr = new Girder(this->worldPhysic.getWorld(), posX, posY, angle, height, width);
        this->girders.insert(std::pair<int, Girder*>(id, girder_ptr));
    }


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

//getModel() 

void World::moveLeft(size_t worm_id) {
    worms[worm_id]->moveLeft();
}

void World::moveRight(size_t worm_id) {
    worms[worm_id]->moveRight();
}

