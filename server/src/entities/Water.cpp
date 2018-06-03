#include "Water.h"

Water::Water(b2World& world, float posX, float posY, float width, float height) :
waterPhysic(world, posX, posY, width, height, this){

}

void Water::update() {

}

float Water::getPosX() {
    return 0;
}

float Water::getPosY() {
    return 0;
}