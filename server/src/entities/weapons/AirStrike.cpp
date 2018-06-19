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
    for (int i = 1; i <= gConfiguration.AIR_STRIKE_MISSIL_QUANTITY; ++i) {
        this->missils.push_back(new Missil(this->id+i,
        this->world,
        this->deploy_x + (i),
        this->deploy_y,
        w_air_strike));
    }
}

std::vector<Missil*> AirStrike::getMissils() {
    return this->missils;
}