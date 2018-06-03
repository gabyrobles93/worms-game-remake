#include "Weapon.h"

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