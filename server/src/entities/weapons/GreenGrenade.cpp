#include "GreenGrenade.h"
#include "types.h"

GreenGrenade::GreenGrenade(b2World& world, float posX, float posY/*, float shooting_angle*/) :
Weapon(w_green_grenade),
greenGrenadePhysic(world, posX, posY) {
    this->exploded = false;
}

void GreenGrenade::update() {
    if (this->delay == 0 && !exploded) {
        explode();
    } else this->delay--;
}

void GreenGrenade::explode() {
    this->greenGrenadePhysic.explode(gConfiguration.GREEN_GRENADE_BLAST_RADIUS, gConfiguration.GREEN_GRENADE_BLAST_POWER);
    this->exploded = true;
}

bool GreenGrenade::hasExploded() {
    return this->exploded;
}