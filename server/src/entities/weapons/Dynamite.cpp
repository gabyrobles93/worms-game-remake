#include "Dynamite.h"
#include <iostream>
#include "types.h"

Dynamite::Dynamite(int id, b2World& world, float posX, float posY, int delay, int currentTime) :
Weapon(w_dynamite),
detonationTime(currentTime + delay),
dynamitePhysic(world, posX, posY) {
    this->exploded = false;
    this->id = id;
    this->blast_radius = gConfiguration.DYNAMITE_BLAST_RADIUS;
}

void Dynamite::update(int currentTime) {
    if (currentTime >= this->detonationTime && !exploded) {
        explode();
    }
    this->countdown = this->detonationTime - currentTime;
}

void Dynamite::explode() {
    this->dynamitePhysic.explode(this->blast_radius, gConfiguration.DYNAMITE_BLAST_POWER);
    this->exploded = true;
}

float Dynamite::getPosX() {
    return this->dynamitePhysic.getPosX();
}

float Dynamite::getPosY() {
    return this->dynamitePhysic.getPosY();
}