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
    return this->weapons.size();
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
    float ceiling_posY = (MAP_HEIGTH) * gConfiguration.SCALING_FACTOR;
    float ceiling_height = 3;
    float ceiling_width = MAP_WIDTH * gConfiguration.SCALING_FACTOR;
    float wall_height = (MAP_HEIGTH / 2) * gConfiguration.SCALING_FACTOR;
    float wall_width = 3;
    float left_wall_posX = 0;
    float right_wall_posX = MAP_WIDTH * gConfiguration.SCALING_FACTOR;
    float wall_posY = (MAP_HEIGTH / 2) * gConfiguration.SCALING_FACTOR;

    Wall ceiling(this->worldPhysic.getWorld(), ceiling_posX, ceiling_posY, ceiling_width, ceiling_height);
    Wall left_wall(this->worldPhysic.getWorld(), left_wall_posX, wall_posY, wall_width, wall_height);
    Wall right_wall(this->worldPhysic.getWorld(), right_wall_posX, wall_posY, wall_height, wall_width);

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

    //this->game_snapshot.updateTeams(this->teams);
}

void World::updateBodies() {
    std::map<int, Weapon*>::iterator it;
    for(it=this->weapons.begin();it != this->weapons.end();) {
        if ((it)->second->hasExploded()) {
            int q_added = it->second->addProjectiles(this->weapons);
            this->weapon_counter = this->weapon_counter + q_added;
            delete (it->second);
            it = this->weapons.erase(it);
        } else {
            (it)->second->update(getTimeSeconds(), wind->getWindForce());
            it++;
        }
    }

    for (std::map<int,Worm*>::iterator it=this->worms.begin(); it != this->worms.end(); ++it) {
        Worm* worm = it->second;
        if (!worm->isDead())
            worm->update();
    }

    for (std::map<int, Girder*>::iterator it = this->girders.begin(); it != this->girders.end(); ++it) {
        Girder* girder = it->second;
        girder->update();
    }

    this->water->update();
}

void World::run() {
    unsigned int step_counter = 0;
    while (this->keep_running) { 
        this->worldPhysic.step();
        this->worldPhysic.clearForces();
        step_counter++;
        if (this->worldPhysic.aliveBodies() || step_counter == 60) {
            Snapshot* snapshot = new Snapshot();            
            snapshot->updateTeams(this->teams);
            snapshot->updateProjectiles(this->weapons);
            this->snapshots.push(snapshot);
        }
        updateBodies();
        if (step_counter == 60) {
            this->time_sec++;
            step_counter = 0;
        }
        usleep(16666);
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
                this->shootWeapon(event, id);
            } else {
                std::cout << "Se ignora disparo porque hay un projectil vivo." << std::endl;
            }
            break;
        }
        default: break;
    }
}

void World::shootWeapon(Event & event, size_t id) {
    const YAML::Node & nodeEvent = event.getNode();
    weapon_t weapon_shooted = (weapon_t) nodeEvent["event"]["weapon"].as<int>();
    Weapon * newWeapon = NULL;

    //if (!this->game_snapshot.hasWeaponSupplies(this->worms[id]->getTeam(), weapon_shooted)) {
    //    std::cout << "Sin municiones, accion ignorada." << std::endl;
    //    return;
    //}

    std::cout << "Quedan municiones entonces dispara." << std::endl;

    if (weapon_shooted == w_dynamite) {
        newWeapon = new Dynamite(this->weapon_counter, this->worldPhysic.getWorld(), this->worms[id]->getPosX(), this->worms[id]->getPosY(), 5, getTimeSeconds());            
    } else if (weapon_shooted == w_green_grenade || weapon_shooted == w_holy_grenade || weapon_shooted == w_banana) {
        newWeapon = new Grenade(
        this->weapon_counter, 
        this->worldPhysic.getWorld(), 
        this->worms[id]->getPosX(), 
        this->worms[id]->getPosY(), 
        this->worms[id]->isMirrored() , 
        nodeEvent["event"]["sight_angle"].as<int>() , 
        nodeEvent["event"]["power"].as<int>(), 
        nodeEvent["event"]["countdown"].as<int>(), 
        getTimeSeconds(), 
        weapon_shooted
        );
    } else if (weapon_shooted == w_bazooka) {
        newWeapon = new Bazooka(this->weapon_counter, 
        this->worldPhysic.getWorld(), 
        this->worms[id]->getPosX(), 
        this->worms[id]->getPosY(),
        this->worms[id]->isMirrored(),
        nodeEvent["event"]["sight_angle"].as<int>(),
        nodeEvent["event"]["power"].as<int>(),
        weapon_shooted
        );
    } else if (weapon_shooted == w_air_strike) {
        AirStrike air_strike(this->weapon_counter,
        this->worldPhysic.getWorld(),
        nodeEvent["event"]["remote_control_x"].as<int>() * gConfiguration.SCALING_FACTOR,
        nodeEvent["event"]["remote_control_y"].as<int>() * gConfiguration.SCALING_FACTOR
        );

        std::vector<Missil*> missils = air_strike.getMissils();
        for (std::vector<Missil*>::iterator it = missils.begin(); it != missils.end(); ++it) {
            //this->game_snapshot.addProjectile((*it));
            this->weapons.insert(std::pair<int, Weapon*>((*it)->getId(), (*it)));
            this->weapon_counter++;
        //    this->game_snapshot.reduceWeaponSupply(this->worms[id]->getTeam(), weapon_shooted);
            this->worms[id]->shoot();
        }
    } else if (weapon_shooted == w_cluster) {
        newWeapon = new RedGrenade(this->weapon_counter,
        this->worldPhysic.getWorld(),
        this->worms[id]->getPosX(),
        this->worms[id]->getPosY(),
        this->worms[id]->isMirrored(),
        nodeEvent["event"]["sight_angle"].as<int>(),
        nodeEvent["event"]["power"].as<int>(),
        nodeEvent["event"]["countdown"].as<int>(), 
        getTimeSeconds(), 
        weapon_shooted
        );
    } else if (weapon_shooted == w_mortar) {
        newWeapon = new Mortar(this->weapon_counter,
        this->worldPhysic.getWorld(),
        this->worms[id]->getPosX(),
        this->worms[id]->getPosY(),
        this->worms[id]->isMirrored(),
        nodeEvent["event"]["sight_angle"].as<int>(),
        nodeEvent["event"]["power"].as<int>(), 
        w_bazooka
        );
    } else if (weapon_shooted == w_bat) {
        std::cout << "ANGULO DE MIRA" << nodeEvent["event"]["sight_angle"];
        Bat bat(this->worldPhysic.getWorld(), 
        this->worms[id]->getPosX(),
        this->worms[id]->getPosY(),
        this->worms[id]->isMirrored(),
        nodeEvent["event"]["sight_angle"].as<int>());
    } else if (weapon_shooted == w_teleport) {
        std::cout << "TELEPORT" << "x " << nodeEvent["event"]["remote_control_x"].as<int>() << "y " << nodeEvent["event"]["remote_control_y"].as<int>()<< std::endl;
        Teleportation teleportation(this->worms[id],
        (float) nodeEvent["event"]["remote_control_x"].as<int>() * gConfiguration.SCALING_FACTOR,
        (float) nodeEvent["event"]["remote_control_y"].as<int>() * gConfiguration.SCALING_FACTOR);
        teleportation.teleport();
    }

    if (newWeapon) {
        this->weapons.insert(std::pair<int, Weapon*>(this->weapon_counter, newWeapon));
        this->weapon_counter++;
        //this->game_snapshot.reduceWeaponSupply(this->worms[id]->getTeam(), weapon_shooted);
        
    }
    this->worms[id]->shoot();  
}
