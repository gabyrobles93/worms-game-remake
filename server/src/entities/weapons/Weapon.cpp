#include "Weapon.h"

Weapon::~Weapon() {
}

bool Weapon::hasExploded() {
    return this->exploded;
}

int Weapon::getCountDown() {
    return this->count_down;
}