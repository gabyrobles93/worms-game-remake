#include "Dynamite.h"
#include <iostream>

Dynamite::Dynamite(b2World& world, float posX, float posY) :
 dynamitePhysic(world, posX, posY) {
     std::cout << "DINAMITA CREADA" << std::endl;

}

void Dynamite::explode() {
    this->dynamitePhysic.explode();
}
