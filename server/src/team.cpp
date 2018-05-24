#include <iostream>
#include <map>
#include "team.h"
#include "Worm.h"

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

std::vector<int> Team::getWormsID(void) {
    std::vector<int> ids;
    std::map<int, Worm*>::const_iterator it;
    for (it = this->worms.begin(); it != this->worms.end(); it++) {
        ids.push_back(it->second->getId());
    }
    return ids;
}

Team::~Team(void) {
}
