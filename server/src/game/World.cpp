#include "World.h"
#include <unistd.h>
#include <iostream>

#define MAP_WIDTH 2500
#define MAP_HEIGTH 1500

World::World(std::string & map_path, Queue<Snapshot*> & snps) :
snapshots(snps),
map_path(map_path) {
    this->map_node = YAML::LoadFile(map_path);
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

    for (std::map<int, Team*>::iterator it = this->teams.begin(); it != this->teams.end(); ++it) {
        delete it->second;
    }

    delete this->water;
    delete this->weaponManager;
    delete this->wind;
    delete this->ceiling;
    delete this->leftWall;
    delete this->rightWall;
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

Wind* World::getWind() {
    return this->wind;
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
    return this->weaponManager->hasAliveWeapons();
}

bool World::hasWormsAffectedByExplosion() {
    for (std::map<int, Worm*>::iterator it = this->worms.begin(); it != this->worms.end(); ++it) {
        if (it->second->isAffectedByExplosion() && !it->second->isDead()) return true;
    }
    return false;
}

bool World::hasWormShooted(size_t worm_id) {
    return this->worms[worm_id]->didShootInTurn();
}

std::map<int, Team*> & World::getTeams() {
    return this->teams;
}

void World::initializeWorld() {
    float water_posX = (MAP_WIDTH / 2) * gConfiguration.SCALING_FACTOR;
    float water_posY = (MAP_HEIGTH - 100) * gConfiguration.SCALING_FACTOR ;
    float water_height = this->map_node["static"]["water_level"].as<int>() * gConfiguration.SCALING_FACTOR;
    float water_width =   MAP_WIDTH * gConfiguration.SCALING_FACTOR;

    this->water = new Water(this->worldPhysic.getWorld(), water_posX, water_posY, water_width, water_height);

    this->wind = new Wind();


    float ceiling_posX = (MAP_WIDTH / 2) * gConfiguration.SCALING_FACTOR;
    float ceiling_posY = 0;
    float ceiling_height = 3; 
    float ceiling_width = MAP_WIDTH * gConfiguration.SCALING_FACTOR;
    float wall_height = MAP_HEIGTH * gConfiguration.SCALING_FACTOR;
    float wall_width = 3;
    float left_wall_posX = 0;
    float right_wall_posX = MAP_WIDTH * gConfiguration.SCALING_FACTOR;
    float wall_posY = (MAP_HEIGTH / 2) * gConfiguration.SCALING_FACTOR;

    this->ceiling = new Wall(this->worldPhysic.getWorld(), ceiling_posX, ceiling_posY, ceiling_width, ceiling_height);
    this->leftWall = new Wall(this->worldPhysic.getWorld(), left_wall_posX, wall_posY, wall_width, wall_height);
    this->rightWall = new Wall(this->worldPhysic.getWorld(), right_wall_posX, wall_posY, wall_width, wall_height);

    const YAML::Node & static_node = this->map_node["static"];
    const YAML::Node & dynamic_node = this->map_node["dynamic"];

    const YAML::Node& short_girders_node = static_node["short_girders"];
    const YAML::Node& long_girders_node = static_node["long_girders"];
    const YAML::Node& worms_teams_node = dynamic_node["worms_teams"];

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

    // Initialize team
    int id, tid, health;
    float x;
    float y;
    std::string name;
    for (YAML::const_iterator it = worms_teams_node.begin(); it != worms_teams_node.end(); it++) {
        tid = it->first.as<int>();
        Team* new_team = new Team(tid);
        const YAML::Node& worms_node = it->second["worms"];
        for (YAML::const_iterator worms_it = worms_node.begin(); worms_it != worms_node.end(); worms_it++) {
            const YAML::Node& worm = *worms_it;
            name = worm["name"].as<std::string>();
            id = worm["id"].as<int>();
            health = worm["health"].as<int>();
            x = (float) worm["x"].as<int>() * gConfiguration.SCALING_FACTOR;
            y = (float) worm["y"].as<int>() * gConfiguration.SCALING_FACTOR;
            Worm * new_worm = new Worm(name, id, tid, health, this->worldPhysic.getWorld(), x, y);
            this->worms.insert(std::pair<int, Worm*>(id, new_worm));
            new_team->addMember(new_worm);
        }
        new_team->initializeInventory(dynamic_node["worms_teams"][tid]["inventory"]);
        this->teams.insert(std::pair<int, Team*>(tid, new_team));
    }

    this->weaponManager = new WeaponManager(this->worms, this->teams, this->worldPhysic);
}

void World::updateBodies() {
    this->weaponManager->updateWeapons(getTimeSeconds(), wind->getWindForce());
    for (std::map<int,Worm*>::iterator it=this->worms.begin(); it != this->worms.end(); ++it) {
        Worm* worm = it->second;
        //if (!worm->isDead())
            worm->update();
    }
}

void World::run() {
    unsigned int step_counter = 0;
    while (this->keep_running) { 
        this->worldPhysic.step();
        this->worldPhysic.clearForces();
        step_counter++;
        if (this->worldPhysic.aliveBodies() || step_counter == 60 /*|| this->weapons.size() > 0*/) {
            Snapshot* snapshot = new Snapshot();            
            snapshot->updateTeams(this->teams);
            snapshot->updateProjectiles(this->weaponManager->getWeapons());
            this->snapshots.push(snapshot);
        }
        updateBodies();
        if (step_counter == 60) {
            this->time_sec++;
            step_counter = 0;
        }
        usleep(16666);
    }
    std::cout << "Sacando ultimas dos fotos." << std::endl;
    for (int i = 0; i < 2; i++) {
        Snapshot* snapshot = new Snapshot();            
        snapshot->updateTeams(this->teams);
        snapshot->updateProjectiles(this->weaponManager->getWeapons());
        this->snapshots.push(snapshot);
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
            this->weaponManager->manageShoot(event, id, getTimeSeconds());
            break;
        }
        case a_pickWeapon:
            this->worms[id]->pickWeapon((weapon_t) eventNode["event"]["weapon"].as<int>());
        default: break;
    }
}