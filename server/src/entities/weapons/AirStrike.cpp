#include "AirStrike.h"

AirStrike::AirStrike(int id, b2World& world, float posX, float posY) : 
//Weapon(w_air_strike),
world(world) {
    this->id = id;
    this->deploy_x = posX;
    this->deploy_y = posY;
    createMissils();
}

AirStrike::~AirStrike() {
    // for(std::vector<Missil*>::iterator it = this->missils.begin(); it != this->missils.end(); ++it) {
    //     delete (*it);
    // }
}

void AirStrike::createMissils() {
    for (int i = 0; i < 6; ++i) {
        this->missils.push_back(new Missil(this->id+i,
        this->world,
        this->deploy_x + (i * 2),
        this->deploy_y,
        w_dynamite));
    }
}

std::vector<Missil*> AirStrike::getMissils() {
    return this->missils;
}