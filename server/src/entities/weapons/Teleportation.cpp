#include "Teleportation.h"

Teleportation::Teleportation(Worm& worm, float posX, float posY) :
worm(worm),
posX(posX),
posY(posY) {

}
void Teleportation::teleport() {
    this->worm.setPosX(this->posX);
    this->worm.setPosY(this->posY);
}