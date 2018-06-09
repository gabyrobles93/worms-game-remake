#include "Girder.h"

Girder::Girder(b2World& world, float posX, float posY, float angle, float height, float width) : 
girderPhysic(world, posX, posY, height, width, angle, this) {

}

float Girder::getPosX() {
	return this->girderPhysic.getPosX();
}

float Girder::getPosY() {
    return this->girderPhysic.getPosY();
}

float Girder::getAngle() {
    return this->girderPhysic.getAngle();
}

Girder::~Girder(void) {
}

void Girder::update() {
    this->girderPhysic.sleep();
}