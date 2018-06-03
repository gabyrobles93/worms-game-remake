#include "Dynamite.h"
#include <iostream>

Dynamite::Dynamite(b2World& world, float posX, float posY, int delay, int currentTime) :
detonationTime(currentTime + delay),
dynamitePhysic(world, posX, posY, delay) {
    this->exploded = false;
}

void Dynamite::update(int currentTime) {
    if (currentTime >= detonationTime && !exploded) {
        explode();
    }
}

void Dynamite::explode() {
    this->dynamitePhysic.explode(BLAST_RADIUS,BLAST_POWER);
    this->exploded = true;
}

bool Dynamite::hasExploded() {
    return this->exploded;
}

float Dynamite::getPosX() {
    return this->dynamitePhysic.getPosX();
}

float Dynamite::getPosY() {
    return this->dynamitePhysic.getPosY();
}
