#include "GreenGrenade.h"

GreenGrenade::GreenGrenade(b2World& world, float posX, float posY/*, float shooting_angle*/) :
greenGrenadePhysic(world, posX, posY){
    this->exploded = false;
}

void GreenGrenade::update() {
    if (this->delay == 0 && !exploded) {
        explode();
    } else this->delay--;
}

void GreenGrenade::explode() {
    this->greenGrenadePhysic.explode(BLAST_RADIUS, BLAST_POWER);
    this->exploded = true;
}

bool GreenGrenade::hasExploded() {
    return this->exploded;
}