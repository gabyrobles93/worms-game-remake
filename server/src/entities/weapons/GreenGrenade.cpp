#include "GreenGrenade.h"
#include "types.h"

GreenGrenade::GreenGrenade(int id, b2World& world, float posX, float posY, float shooting_angle, int power_factor, int delay, int currentTime) :
Weapon(w_green_grenade),
detonationTime(currentTime + delay),
greenGrenadePhysic(world, posX, posY) {
    this->exploded = false;
}

void GreenGrenade::update(int currentTime) {
    if (currentTime >= this->detonationTime && !exploded) {
        explode();
    }
    this->countdown = this->detonationTime - currentTime;
}

void GreenGrenade::explode() {
    this->greenGrenadePhysic.explode(gConfiguration.GREEN_GRENADE_BLAST_RADIUS, gConfiguration.GREEN_GRENADE_BLAST_POWER);
    this->exploded = true;
}

bool GreenGrenade::hasExploded() {
    return this->exploded;
}

float GreenGrenade::getPosX() {
    return this->greenGrenadePhysic.getPosX();
}

float GreenGrenade::getPosY() {
    return this->greenGrenadePhysic.getPosY();
}

void GreenGrenade::shoot() {
    this->greenGrenadePhysic.shoot();
}