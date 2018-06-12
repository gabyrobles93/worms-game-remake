#include "Teleportation.h"
#include "types.h"
#include <iostream>

Teleportation::Teleportation(Worm* worm, float posX, float posY) :
posX(posX),
posY(posY) {
    this->worm = worm;

}
void Teleportation::teleport() {
    std::cout << " EN TELEPORT " << this->posX << " y " << this->posY << std::endl;
    this->worm->setPosition(posX, posY);
}
