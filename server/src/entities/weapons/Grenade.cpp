#include "Grenade.h"
#include "types.h"

Grenade::Grenade(int id, b2World& world, float posX, float posY, bool mirrored, float shooting_angle, int power_factor, int delay, int currentTime, weapon_t type) :
Weapon(type),
detonationTime(currentTime + delay),
grenadePhysic(world, posX, posY) {
    this->exploded = false;
    this->power_factor = power_factor;
    this->mirrored = mirrored;
    this->shooting_angle = shooting_angle;
    this->id = id;

    if (type == w_banana) {
        this->blast_power = gConfiguration.BANANA_BLAST_POWER;
        this->blast_radius = gConfiguration.BANANA_BLAST_RADIUS;
    } else if (type == w_holy_grenade) {
        this->blast_power = gConfiguration.HOLY_GRENADE_BLAST_POWER;
        this->blast_radius = gConfiguration.HOLY_GRENADE_BLAST_RADIUS;
    } else if (type == /*w_green_grenade*/ w_dynamite) {
        this->blast_power = gConfiguration.GREEN_GRENADE_BLAST_POWER;
        this->blast_radius = gConfiguration.GREEN_GRENADE_BLAST_RADIUS;
    }
    shoot();
}

void Grenade::update(int currentTime) {
    if (currentTime >= this->detonationTime && !exploded) {
        explode();
    }
    this->countdown = this->detonationTime - currentTime;
}

void Grenade::explode() {
    this->grenadePhysic.explode(this->blast_radius, this->blast_power);
    this->exploded = true;
}

bool Grenade::hasExploded() {
    return this->exploded;
}

float Grenade::getPosX() {
    return this->grenadePhysic.getPosX();
}

float Grenade::getPosY() {
    return this->grenadePhysic.getPosY();
}

void Grenade::shoot() {
    this->grenadePhysic.shoot(mirrored, shooting_angle);
}