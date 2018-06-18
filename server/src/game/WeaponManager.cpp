#include "WeaponManager.h"

WeaponManager::WeaponManager(std::map<int, Worm*> & worms, std::map<int, Team*> & teams, WorldPhysic & world) :
worms(worms),
world(world),
teams(teams) {
    this->weaponCounter = 0;
}

void WeaponManager::manageShoot(Event & event, size_t id, unsigned int currentTime) {
    if ((this->weapons.size() != 0) || this->worms[id]->didShootInTurn()) {
        return;
    }
    
    const YAML::Node & nodeEvent = event.getNode();
    weapon_t weapon = (weapon_t) nodeEvent["event"]["weapon"].as<int>();

    if (!this->teams[this->worms[id]->getTeam()]->hasSupplies(weapon)) {
        std::cout << "Disparo ignorado, no quedan supplies." << std::endl;
        return;
    }

    std::cout << "Quedan municiones entonces dispara." << std::endl;

    Weapon* newWeapon = NULL;

    if (weapon == w_dynamite) {
        newWeapon = new Dynamite(this->weaponCounter,
        this->world.getWorld(), 
        this->worms[id]->getPosX(), 
        this->worms[id]->getPosY(), 
        nodeEvent["event"]["countdown"].as<int>(), 
        currentTime
        );            
    } else if (weapon == w_green_grenade || weapon == w_holy_grenade || weapon == w_banana) {
        newWeapon = new Grenade(
        this->weaponCounter, 
        this->world.getWorld(), 
        this->worms[id]->getPosX(), 
        this->worms[id]->getPosY(), 
        this->worms[id]->isMirrored() , 
        nodeEvent["event"]["sight_angle"].as<int>() , 
        nodeEvent["event"]["power"].as<int>(), 
        nodeEvent["event"]["countdown"].as<int>(), 
        currentTime, 
        weapon
        );
    } else if (weapon == w_bazooka) {
        newWeapon = new Bazooka(this->weaponCounter, 
        this->world.getWorld(), 
        this->worms[id]->getPosX(), 
        this->worms[id]->getPosY(),
        this->worms[id]->isMirrored(),
        nodeEvent["event"]["sight_angle"].as<int>(),
        nodeEvent["event"]["power"].as<int>(),
        weapon
        );
    } else if (weapon == w_air_strike) {
        AirStrike air_strike(this->weaponCounter,
        this->world.getWorld(),
        nodeEvent["event"]["remote_control_x"].as<int>() * gConfiguration.SCALING_FACTOR,
        nodeEvent["event"]["remote_control_y"].as<int>() * gConfiguration.SCALING_FACTOR
        );

        std::vector<Missil*> missils = air_strike.getMissils();
        for (std::vector<Missil*>::iterator it = missils.begin(); it != missils.end(); ++it) {
            this->weapons.insert(std::pair<int, Weapon*>((*it)->getId(), (*it)));
            this->weaponCounter++;
            this->worms[id]->shoot();
        }
    } else if (weapon == w_cluster) {
        newWeapon = new RedGrenade(this->weaponCounter,
        this->world.getWorld(),
        this->worms[id]->getPosX(),
        this->worms[id]->getPosY(),
        this->worms[id]->isMirrored(),
        nodeEvent["event"]["sight_angle"].as<int>(),
        nodeEvent["event"]["power"].as<int>(),
        nodeEvent["event"]["countdown"].as<int>(), 
        currentTime, 
        weapon
        );
    } else if (weapon == w_mortar) {
        newWeapon = new Mortar(this->weaponCounter,
        this->world.getWorld(),
        this->worms[id]->getPosX(),
        this->worms[id]->getPosY(),
        this->worms[id]->isMirrored(),
        nodeEvent["event"]["sight_angle"].as<int>(),
        nodeEvent["event"]["power"].as<int>(), 
        weapon
        );
    } else if (weapon == w_bat) {
        std::cout << "ANGULO DE MIRA" << nodeEvent["event"]["sight_angle"];
        Bat bat(this->world.getWorld(), 
        this->worms[id]->getPosX(),
        this->worms[id]->getPosY(),
        this->worms[id]->isMirrored(),
        nodeEvent["event"]["sight_angle"].as<int>());
    } else if (weapon == w_teleport) {
        std::cout << "TELEPORT" << "x " << nodeEvent["event"]["remote_control_x"].as<int>() << "y " << nodeEvent["event"]["remote_control_y"].as<int>()<< std::endl;
        Teleportation teleportation(this->worms[id],
        (float) nodeEvent["event"]["remote_control_x"].as<int>() * gConfiguration.SCALING_FACTOR,
        (float) nodeEvent["event"]["remote_control_y"].as<int>() * gConfiguration.SCALING_FACTOR);
        teleportation.teleport();
    }

    if (newWeapon) {
        this->weapons.insert(std::pair<int, Weapon*>(this->weaponCounter, newWeapon));
        this->weaponCounter++;
    }

    this->teams[this->worms[id]->getTeam()]->reduceSupplie(weapon);
    this->worms[id]->shoot();
}

void WeaponManager::updateWeapons(unsigned int currentTime, int windForce) {
    std::map<int, Weapon*>::iterator it;
    for(it=this->weapons.begin();it != this->weapons.end();) {
        if ((it)->second->hasExploded()) {
            int q_added = it->second->addProjectiles(this->weapons);
            this->weaponCounter = this->weaponCounter + q_added;
            delete (it->second);
            it = this->weapons.erase(it);
        } else {
            (it)->second->update(currentTime, windForce);
            it++;
        }
    }
}

std::map<int, Weapon*> & WeaponManager::getWeapons() {
    return this->weapons;
}

bool WeaponManager::hasAliveWeapons() {
    return this->weapons.size();
}

