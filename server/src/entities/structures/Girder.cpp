#include "Girder.h"

Girder::Girder(b2World& world, float posX, float posY, float angle, float height, float width) : 
girderPhysic(world, posX, posY, height, width, angle) {

}

float Girder::getPosX() {
    this->girderPhysic.getPosX();
}

float Girder::getPosY() {
    this->girderPhysic.getPosY();
}

float Girder::getAngle() {
    this->girderPhysic.getAngle();
}