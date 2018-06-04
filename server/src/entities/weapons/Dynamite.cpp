#include "Dynamite.h"
#include <iostream>

Dynamite::Dynamite(int id, b2World& world, float posX, float posY, int delay, int currentTime) :
detonationTime(currentTime + delay),
dynamitePhysic(world, posX, posY) {
    this->exploded = false;
    this->id = id;
}

void Dynamite::update(int currentTime) {
    if (currentTime >= this->detonationTime && !exploded) {
        explode();
    }
    this->countdown = this->detonationTime - currentTime;
}

void Dynamite::explode() {
    this->dynamitePhysic.explode(gConfiguration.DYNAMITE_BLAST_RADIUS, gConfiguration.DYNAMITE_BLAST_POWER);
    this->exploded = true;
}

float Dynamite::getPosX() {
    return this->dynamitePhysic.getPosX();
}

float Dynamite::getPosY() {
    return this->dynamitePhysic.getPosY();
}