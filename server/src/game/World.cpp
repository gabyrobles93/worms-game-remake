#include "World.h"
#include <unistd.h>
#include <iostream>

#define MAP_WIDTH 2500
#define MAP_HEIGTH 1500
#define WATER_LEVEL 300

World::World(std::string & map_path, Queue<YAML::Node> & snps) :
snapshots(snps) {
    this->node_map = YAML::LoadFile(map_path);
    initializeWorld();
    this->keep_running = true;
    this->time_sec = 0;
    this->weapon_counter = 0;
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

std::map<int, Worm *> & World::getWorms() {
    return this->worms;
}

void World::initializeWorld() {
    float water_posX = (MAP_WIDTH / 2) * SCALING_FACTOR;
    float water_posY = (MAP_HEIGTH - 100) * SCALING_FACTOR ;
    float water_height = WATER_LEVEL * SCALING_FACTOR;
    float water_width =   MAP_WIDTH * SCALING_FACTOR;

    this->water = new Water(this->worldPhysic.getWorld(), water_posX, water_posY, water_width, water_height);
    const YAML::Node& static_node = this->node_map["static"];
    const YAML::Node& dynamic_node = this->node_map["dynamic"];

    const YAML::Node & short_girders_node = static_node["short_girders"];
    const YAML::Node & long_girders_node = static_node["long_girders"];

    const YAML::Node& worms_teams_node = dynamic_node["worms_teams"];

    for (YAML::const_iterator it = short_girders_node.begin(); it != short_girders_node.end(); ++it) {
        const YAML::Node &  short_girder = *it;
        int id = short_girder["id"].as<int>();
        float posX = (float) short_girder["x"].as<int>() * SCALING_FACTOR;
        float posY = (float) short_girder["y"].as<int>() * SCALING_FACTOR;
        float angle = (float) short_girder["angle"].as<int>() * GRADTORAD;
        Girder* girder_ptr = new Girder(this->worldPhysic.getWorld(), posX, posY, -angle, 0.8, 3);
        this->girders.insert(std::pair<int, Girder*>(id, girder_ptr));
    }

    for (YAML::const_iterator it = long_girders_node.begin(); it != long_girders_node.end(); ++it) {
        const YAML::Node&  long_girder = *it;
        int id = long_girder["id"].as<int>();
        float posX = (float) long_girder["x"].as<int>() * SCALING_FACTOR;
        float posY = (float) long_girder["y"].as<int>() * SCALING_FACTOR;
        float angle = (float) long_girder["angle"].as<int>() * GRADTORAD;
        Girder* girder_ptr = new Girder(this->worldPhysic.getWorld(), posX, posY, -angle, 0.8, 6);
        this->girders.insert(std::pair<int, Girder*>(id, girder_ptr));
    }

    int id, tid, health;
    float x;
    float y;
    std::string name;
    for (YAML::const_iterator it = worms_teams_node.begin(); it != worms_teams_node.end(); it++) {
        const YAML::Node& worms_node = it->second["worms"];
        tid = it->first.as<int>();
        for (YAML::const_iterator worms_it = worms_node.begin(); worms_it != worms_node.end(); worms_it++) {
            const YAML::Node& worm = *worms_it;
            name = worm["name"].as<std::string>();
            id = worm["id"].as<int>();
            health = worm["health"].as<int>();
            x = (float) worm["x"].as<int>() * SCALING_FACTOR;
            y = (float) worm["y"].as<int>() * SCALING_FACTOR;
            Worm * new_worm = new Worm(name, id, tid, health, this->worldPhysic.getWorld(), x, y);
            this->worms.insert(std::pair<int, Worm*>(id, new_worm));
        }
    }
}

void World::updateYAML() {
    updateWormsYAML();
    updateProjectilesYAML();
}

void World::updateProjectilesYAML(void) {
    std::string x;
    std::string y;
    std::string current_time;
    std::string exploded;
    YAML::Node::iterator it;
    for (it = this->node_map["dynamic"]["projectiles"].begin(); it !=this->node_map["dynamic"]["projectiles"].end(); it++) {
        YAML::Node projectile = *it;
        int weapon_id = projectile["id"].as<int>();
        x = std::to_string((int) this->weapons[weapon_id]->getPosX());
        y = std::to_string((int) this->weapons[weapon_id]->getPosY());
        current_time = std::to_string(this->weapons[weapon_id]->getCountdown());
        exploded = std::to_string(this->weapons[weapon_id]->hasExploded());
        projectile["x"] = x;
        projectile["y"] = y;
        projectile["countdown"] = current_time;
        projectile["exploded"] = exploded;
    }
}

void World::updateWormsYAML(void) {
    YAML::Node::iterator it;
    std::string x;
    std::string y;
    std::string health;
    std::string mirrored;
    std::string walking;
    std::string falling;
    std::string grounded;

    for (it = this->node_map["dynamic"]["worms_teams"].begin(); it !=this->node_map["dynamic"]["worms_teams"].end(); it++) {
        YAML::Node worms_node = it->second["worms"];
        for (YAML::iterator worms_it = worms_node.begin(); worms_it != worms_node.end(); worms_it++) {
            YAML::Node worm = *worms_it;
            int id = worm["id"].as<int>();
            x = std::to_string((int) (this->worms[id]->getPosX() / SCALING_FACTOR));
            y = std::to_string((int) (this->worms[id]->getPosY() / SCALING_FACTOR));
            health = std::to_string(this->worms[id]->getHealth());
            mirrored = std::to_string(this->worms[id]->isMirrored());
            walking = std::to_string(this->worms[id]->isWalking());
            falling = std::to_string(this->worms[id]->isFalling());
            grounded = std::to_string(this->worms[id]->isGrounded());
            worm["x"] = x;
            worm["y"] = y;
            worm["health"] = health;
            worm["status"]["mirrored"] = mirrored;
            worm["status"]["walking"] = walking;
            worm["status"]["falling"] = falling;
            worm["status"]["grounded"] = grounded;
        }
    }
}

void World::updateBodies() {
    std::map<int, Weapon*>::iterator it;
    for(it=this->weapons.begin();it != this->weapons.end();) {
        if ((it)->second->hasExploded()) {
            removeProjectileFromYAML(it->second->getId());
            delete (it->second);
            it = this->weapons.erase(it);
        } else {
            (it)->second->update(getTimeSeconds());
            it++;
        }
    }

    for (std::map<int,Worm*>::iterator it=this->worms.begin(); it != this->worms.end(); ++it) {
        Worm* worm = it->second;
        if (!worm->isDead())
            worm->update();
    }
}

void World::removeProjectileFromYAML(size_t id) {
    /* YAML::Node::iterator it; */
    //int index = 0;
    std::vector<YAML::Node> vec_projectiles = this->node_map["dynamic"]["projectiles"].as<std::vector<YAML::Node>>();
    std::vector<YAML::Node>::iterator it;
    for (it = vec_projectiles.begin(); it != vec_projectiles.end(); it++) {
        if ((*it)["id"].as<size_t>() == id) {
            it = vec_projectiles.erase(it);
            break;
        }
    }
    
    this->node_map["dynamic"]["projectiles"];
    this->node_map["dynamic"]["projectiles"] = vec_projectiles;

/*     for (unsigned int i = 0; i < this->node_map["dynamic"]["projectiles"].size(); i++) {
        if (this->node_map["dynamic"]["projectiles"][i]["id"].as<size_t>() == id) {
            this->node_map["dynamic"]["projectiles"].remove(i);
            break;
        }
    } */
}

void World::run() {
    unsigned int step_counter = 0;
    while (this->keep_running) {
        usleep(16666);
        this->worldPhysic.step();
        this->worldPhysic.clearForces();
        updateBodies();
        updateYAML();
        this->snapshots.push(getSnapshot());
        step_counter++;

        if (step_counter == 60) {
            this->time_sec++;
            step_counter = 0;
        }
    }
}

YAML::Node World::getSnapshot() {
    return this->node_map["dynamic"];
}

void World::stop() {
    this->keep_running = false;
}

unsigned int World::getTimeSeconds(void) {
    return this->time_sec;
}

void World::executeAction(action_t action, size_t id) {
    switch(action) {
        case a_moveLeft:
            this->worms[id]->moveLeft();
            break;
        case a_moveRight:
            this->worms[id]->moveRight();
            break;
        case a_frontJump:
            this->worms[id]->frontJump();
            break;
        case a_backJump:
            this->worms[id]->backJump();
            break;
        case a_shoot : {
            if (this->weapons.size() == 0) {
                Weapon* dynamite= new Dynamite(weapon_counter, this->worldPhysic.getWorld(), this->worms[id]->getPosX(), this->worms[id]->getPosY(), 5, getTimeSeconds());
                this->weapons.insert(std::pair<int, Weapon*>(weapon_counter, dynamite));
                YAML::Node new_projectile;
                new_projectile["id"] = std::to_string(weapon_counter);
                new_projectile["type"] = "Dynamite";
                new_projectile["x"] = std::to_string(dynamite->getPosX());
                new_projectile["y"] = std::to_string(dynamite->getPosY());
                new_projectile["deton_time"] = std::to_string(5);
                new_projectile["countdown"] = std::to_string(5);
                new_projectile["exploded"] = std::to_string(dynamite->hasExploded());
                this->node_map["dynamic"]["projectiles"].push_back(new_projectile);
                weapon_counter++;
            }
            break;
        }
        default: break;
    }

}
