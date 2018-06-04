#include "Weapon.h"

Weapon::Weapon(weapon_t t) {
    this->type = t;
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