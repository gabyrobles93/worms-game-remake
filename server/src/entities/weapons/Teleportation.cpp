#include "Teleportation.h"
#include "types.h"

Teleportation::Teleportation(Worm& worm, float posX, float posY) :
Weapon(w_teleport),
worm(worm),
posX(posX),
posY(posY) {

}
void Teleportation::teleport() {
    this->worm.setPosX(this->posX);
    this->worm.setPosY(this->posY);
}

bool Teleportation::isMoving() {
    return false;
}