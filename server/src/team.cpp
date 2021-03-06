#include <iostream>
#include <map>
#include "team.h"
#include "Worm.h"
#include "types.h"

Team::Team(int id) {
    this->team_id = id;
    this->member_qty = 0;
}

void Team::addMember(Worm * worm) {
    this->worms[worm->getId()] = worm;
    this->member_qty++;
}

void Team::print(void) const {
    std::map<int, Worm*>::const_iterator it;
    size_t i = 1;
    std::cout << "*********************" << std::endl;
    for (it = this->worms.begin(); it != this->worms.end(); it++) {
        std::cout << "Equipo ID: " << this->team_id << std::endl;
        std::cout << "Miembro " << i++ << std::endl;
        std::cout << "Nombre: " << it->second->getName() << std::endl;
        std::cout << "Vida: " << it->second->getHealth() << std::endl;
        std::cout << "* * * * * * * * * * *" << std::endl; 
    }
    std::cout << "*********************" << std::endl;
}

void Team::initializeInventory(YAML::Node inventory_node) {
    YAML::Node::const_iterator it;
    for (it = inventory_node.begin(); it != inventory_node.end(); it++) {
        weapon_t weapon_id = (weapon_t) it->first.as<int>();
        int supplies = it->second["supplies"].as<int>();
        this->inventory.insert(std::pair<weapon_t,int>(weapon_id, supplies));
    }
}

std::vector<int> Team::getWormsID(void) {
    std::vector<int> ids;
    std::map<int, Worm*>::const_iterator it;
    for (it = this->worms.begin(); it != this->worms.end(); it++) {
        ids.push_back(it->second->getId());
    }
    return ids;
}

int Team::getTeamId(void) {
    return this->team_id;
}

Team::~Team(void) {
}

bool Team::haveAliveMember(void) {
    std::map<int, Worm*>::const_iterator it;
    for (it = this->worms.begin(); it != this->worms.end(); it++) {
        if (!it->second->isDead()) {
            return true;
        }
    }
    return false;
}

int Team::getTotalLife(void) {
    int counter = 0;
    std::map<int, Worm*>::const_iterator it;
    for (it = this->worms.begin(); it != this->worms.end(); it++) {
        counter += it->second->getHealth();
    }
    return counter;
}

std::map<int, Worm*> & Team::getWorms() {
    return this->worms;
}

std::map<weapon_t, int> & Team::getInventory() {
    return this->inventory;
}

void Team::killAll(void) {
    std::map<int, Worm*>::iterator it;
    for (it = this->worms.begin(); it != this->worms.end(); it ++) {
        it->second->kill();
    }
}

bool Team::hasSupplies(weapon_t weapon_id) {
    return this->inventory[weapon_id] > 0;
}

void Team::reduceSupplie(weapon_t weapon_id) {
    this->inventory[weapon_id] -= 1;
}