#include "World.h"
#include <unistd.h>
#include <iostream>

#define MAP_WIDTH 2500
#define MAP_HEIGTH 1500
// #define WATER_LEVEL 300

World::World(std::string & map_path, Queue<Snapshot> & snps) :
snapshots(snps),
game_snapshot(YAML::LoadFile(map_path)) {
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

bool World::hasWormsMoving() {
    for (std::map<int, Worm*>::iterator it = this->worms.begin(); it != this->worms.end(); ++it) {
        if (it->second->isMoving() && !it->second->isDead()) return true;
    }
    return false;
}

bool World::hasWormGotHurt(size_t worm_id) {
    return this->worms[worm_id]->gotHurtInTurn();
}

bool World::hasAliveProjectiles() {
    return this->weapons.size();
}

bool World::hasWormsAffectedByExplosion() {
    for (std::map<int, Worm*>::iterator it = this->worms.begin(); it != this->worms.end(); ++it) {
        if (it->second->isAffectedByExplosion() && !it->second->isDead()) return true;
    }
    return false;
}

void World::initializeWorld() {
    float water_posX = (MAP_WIDTH / 2) * gConfiguration.SCALING_FACTOR;
    float water_posY = (MAP_HEIGTH - 100) * gConfiguration.SCALING_FACTOR ;
    float water_height = this->game_snapshot.getWaterLevel() * gConfiguration.SCALING_FACTOR;
    float water_width =   MAP_WIDTH * gConfiguration.SCALING_FACTOR;

    this->water = new Water(this->worldPhysic.getWorld(), water_posX, water_posY, water_width, water_height);

    YAML::Node short_girders_node = this->game_snapshot.getShortGirders();
    YAML::Node long_girders_node = this->game_snapshot.getLongGirders();
    YAML::Node worms_teams_node = this->game_snapshot.getWormsTeams();

    // Initialize de vigas cortas
    for (YAML::const_iterator it = short_girders_node.begin(); it != short_girders_node.end(); ++it) {
        const YAML::Node &  short_girder = *it;
        int id = short_girder["id"].as<int>();
        float posX = (float) short_girder["x"].as<int>() * gConfiguration.SCALING_FACTOR;
        float posY = (float) short_girder["y"].as<int>() * gConfiguration.SCALING_FACTOR;
        float angle = (float) short_girder["angle"].as<int>() * GRADTORAD;
        Girder* girder_ptr = new Girder(this->worldPhysic.getWorld(), posX, posY, -angle, 0.8, 3);
        this->girders.insert(std::pair<int, Girder*>(id, girder_ptr));
    }

    // Initialize de vigas largas
    for (YAML::const_iterator it = long_girders_node.begin(); it != long_girders_node.end(); ++it) {
        const YAML::Node&  long_girder = *it;
        int id = long_girder["id"].as<int>();
        float posX = (float) long_girder["x"].as<int>() * gConfiguration.SCALING_FACTOR;
        float posY = (float) long_girder["y"].as<int>() * gConfiguration.SCALING_FACTOR;
        float angle = (float) long_girder["angle"].as<int>() * GRADTORAD;
        Girder* girder_ptr = new Girder(this->worldPhysic.getWorld(), posX, posY, -angle, 0.8, 6);
        this->girders.insert(std::pair<int, Girder*>(id, girder_ptr));
    }

    // Initialize de worms
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
            x = (float) worm["x"].as<int>() * gConfiguration.SCALING_FACTOR;
            y = (float) worm["y"].as<int>() * gConfiguration.SCALING_FACTOR;
            Worm * new_worm = new Worm(name, id, tid, health, this->worldPhysic.getWorld(), x, y);
            this->worms.insert(std::pair<int, Worm*>(id, new_worm));
        }
    }
}

void World::updateSnapshot() {
    this->game_snapshot.updateWorms(this->worms);
    this->game_snapshot.updateProjectiles(this->weapons);
}

void World::updateBodies() {
    std::map<int, Weapon*>::iterator it;
    for(it=this->weapons.begin();it != this->weapons.end();) {
        if ((it)->second->hasExploded()) {
            this->game_snapshot.removeProjectile(it->second->getId());
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

void World::run() {
    unsigned int step_counter = 0;
    while (this->keep_running) {
        usleep(16666);
        this->worldPhysic.step();
        this->worldPhysic.clearForces();
        updateBodies();
        updateSnapshot();
        this->snapshots.push(this->game_snapshot);
        step_counter++;

        if (step_counter == 60) {
            this->time_sec++;
            std::cout << "Timer: " << this->time_sec << std::endl;
            step_counter = 0;
        }
    }
}

void World::stop() {
    this->keep_running = false;
}

unsigned int World::getTimeSeconds(void) {
    return this->time_sec;
}

void World::executeAction(Event & event, size_t id) {
    YAML::Node eventNode = event.getNode();
    action_t action = (action_t) eventNode["event"]["action"].as<int>();
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
                weapon_t weapon_shooted = (weapon_t) event.getNode()["event"]["weapon"].as<int>();
                if (this->game_snapshot.hasWeaponSupplies(this->worms[id]->getTeam(), weapon_shooted)) { 
                    std::cout << "Quedan municiones entonces dispara." << std::endl;
                    Weapon * dynamite = new Dynamite(this->weapon_counter, this->worldPhysic.getWorld(), this->worms[id]->getPosX(), this->worms[id]->getPosY(), 5, getTimeSeconds());
                    //Weapon * dynamite = new Grenade(this->weapon_counter, this->worldPhysic.getWorld(), this->worms[id]->getPosX(), this->worms[id]->getPosY(),30 , 1, 3, getTimeSeconds(), w_dynamite);
                    //dynamite.shoot();
                    this->game_snapshot.addProjectile(dynamite);
                    this->weapons.insert(std::pair<int, Weapon*>(this->weapon_counter, dynamite));
                    this->weapon_counter++;
                    this->game_snapshot.reduceWeaponSupply(this->worms[id]->getTeam(), weapon_shooted);                   
                } else {
                    std::cout << "Sin municiones, accion ignorada." << std::endl;
                    return;
                }
            } else {
                std::cout << "Se ignora disparo porque hay un projectil vivo." << std::endl;
            }
            break;
        }
        
        case a_pointUp:
            this->worms[id]->pointHigher();
            break;

        case a_pointDown:
            this->worms[id]->pointMoreDown();
            break;
        default: break;
    }
}
