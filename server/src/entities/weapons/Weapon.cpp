#include "Weapon.h"

Weapon::~Weapon() {
}

bool Weapon::hasExploded() {
    return this->exploded;
}