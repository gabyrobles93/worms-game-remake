#include "Weapon.h"

Weapon::Weapon(weapon_t t) {
    this->type = t;
    this->countdown = -1;
    this->exploded = false;
    this->direction_angle = 0;
    this->wind_affected = false;
}

Weapon::~Weapon() {
}

bool Weapon::hasExploded() {
    return this->exploded;
}

int Weapon::getCountdown() {
    return this->countdown;
}

int Weapon::getId() {
    return this->id;
}

weapon_t Weapon::getType(void) {
    return this->type;
}

int Weapon::getBlastRadius() {
    return this->blast_radius;
}

int Weapon::getDirectionAngle() {
    return this->direction_angle;
}