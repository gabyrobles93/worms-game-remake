#include "World.h"

World::World() {
    WorldPhysic worldPhysic;
    this->worldPhysic = worldPhysic;
}

void World::initializeWorld() {
    YAML::Node world_file = YAML::LoadFile("world.yml");
    YAML::Node girders = world_file["girder"];
    YAML::Node worms = world_file["worms"];

    for (YAML::const_iterator it = girders.begin(); it != girders.end(); ++it) {
        YAML::Node girder = *it;
        int id = girder["id"].as<int>();
        float posX = girder["x"].as<float>();
        float posY = girder["y"].as<float>();
        float angle = girder["angle"].as<float>();
        float height = girder["height"].as<float>();
        float width = girder["width"].as<float>();
        Girder* girder_ptr = new Girder(this->worldPhysic.getWorld(), posX, posY, angle, height, width);
        this->girders.insert(std::pair<int, Girder*>(id, girder_ptr));
    }

    //for (YAML::const_iterator it = worms.begin(); it != worms.end() ; ++it) {

    //}
}