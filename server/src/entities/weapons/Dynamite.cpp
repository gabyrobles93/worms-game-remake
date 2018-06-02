#include "Dynamite.h"
#include <iostream>

Dynamite::Dynamite(b2World& world, float posX, float posY,int delay) :
delay(delay * TIME_FACTOR), 
dynamitePhysic(world, posX, posY, delay) {
    this->exploded = false;
}

void Dynamite::update() {
    if (this->delay == 0 && !exploded) {
        explode();
    } else this->delay--;
}

void Dynamite::explode() {
    this->dynamitePhysic.explode(BLAST_RADIUS,BLAST_POWER);
    this->exploded = true;
}

bool Dynamite::hasExploded() {
    this->exploded;
}
