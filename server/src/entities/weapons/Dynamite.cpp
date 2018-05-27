#include "Dynamite.h"
#include <iostream>

Dynamite::Dynamite(b2World& world, float posX, float posY,int delay) :
dynamitePhysic(world, posX, posY, delay) {
    this->exploded = false;
}

void Dynamite::update() {
    this->dynamitePhysic.update();
    this->exploded = this->dynamitePhysic.hasExploded();
}

void Dynamite::explode() {
    this->dynamitePhysic.explode();
}
