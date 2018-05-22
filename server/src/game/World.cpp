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
    const YAML::Node& static_node = mapNode["static"];
    this->dynamic_node = mapNode["dynamic"];

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

void World::updateWorld() {
    const YAML::Node& worms_node = this->dynamic_node["worms"];
    int id;

    for (YAML::Node worm : worms_node) {
        id = worm["id"].as<int>();
        worm["x"] = (int) this->worms[id]->getPosX();
        worm["y"] = (int) this->worms[id]->getPosY();
    }

    // for (YAML::const_iterator it = worms_node.begin(); it != worms_node.end(); it++) {
    //     const YAML::Node& worm = *it;

    //     id = worm["id"].as<int>();
    
        // worm["x"] = (int) this->worms[id]->getPosX();
        // worm["y"] = (int) this->worms[id]->getPosY();
        //std::cout << this->worms[id]->getPosX() << std::endl;
        //std::cout << this->worms[id]->getPosY() << std::endl;
    //}
    //std::cout << "ACTUALIZO MUNDO " << std::endl;
    // std::map<int, Worm*>::iterator it;
    // for (it = this->worms.begin(); it != this->worms.end(); ++it) {
    //    int id = it->first;

 	// 	std::cout << "Nuevo worm: " << std:: endl;
	// 	std::cout << "Id: " << this->dynamic_node["worms"]["id"].as<int>() << std::endl;
    //     std::cout << "Nombre: " << this->dynamic_node["worms"]["name"].as<std::string>() << std::endl;
    //     std::cout << "Team Id: " << this->dynamic_node["worms"]["team"].as<int>() << std::endl;
	// 	std::cout << "Pos X: " << this->dynamic_node["worms"]["x"].as<int>() << std::endl;
	// 	std::cout << "Pos Y: " << this->dynamic_node["worms"]["y"].as<int>() << std::endl;

    //    std::cout << "EL ID ES " << id << std::endl;
    //    std::cout << this->dynamic_node["worms"][std::to_string(id)]["name"].as<std::string>() << std::endl;
    //    //this->dynamic_node["worms"][id]["x"] = worms[id]->getPosX();
    //    //this->dynamic_node["worms"][id]["y"] = worms[id]->getPosY();
    // }
}

void World::run() {
    while (this->keep_running) {
        this->worldPhysic.step();
        this->worldPhysic.clearForces();
        //updateWorld();
    }
}

// std::string World::getModel() {
//     std::stringstream node_stream;
//     node_stream << this->dynamic_node;
//     return node_stream.str();
// }

YAML::Node World::getSnapshot() {
    YAML::Emitter snapshot;
    snapshot << YAML::BeginMap;
    snapshot << YAML::Key << "worms";
    int id;
    Worm* worm = nullptr;
    for (std::map<int, Worm*>::iterator it = this->worms.begin(); it != this->worms.end(); ++it) {
        worm = it->second;
        snapshot << YAML::BeginMap;
        snapshot << YAML::Key << "id" << YAML::Value << worm->getId();
        //snapshot << YAML::Value << worm->getId();;
        snapshot << YAML::Key << "team";
        snapshot << YAML::Value << worm->getTeam();
        snapshot << YAML::Key << "name";
        snapshot << YAML::Value << worm->getName();
        snapshot << YAML::Key << "health";
        snapshot << YAML::Value << worm->getHealth();
        snapshot << YAML::Key << "x";
        snapshot << YAML::Value << (int) worm->getPosX();
        snapshot << YAML::Key << "y";
        snapshot << YAML::Value <<  (int) worm->getPosY();
        snapshot << YAML::EndMap;
    }
    snapshot << YAML::EndMap;

    std::string pepe(snapshot.c_str());
    
    std::cout << pepe << std::endl;
    
    YAML::Node node(pepe);

    std::stringstream ss;
    ss << node;
    //std::cout << ss.str() << std::endl;

    return node;
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
