#include "Weapon.h"

Weapon::~Weapon() {
}

bool Weapon::hasExploded() {
    return this->exploded;
}

int Weapon::getActiveTime() {
    return this->activeTime;
}