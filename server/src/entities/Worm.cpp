#include "Worm.h"

Worm::Worm(int id, b2World& world, float posX, float posY) : wormPhysic(world, posX, posY) {
    this->id = id;
}

void Worm::jump() {
    this->wormPhysic.jump();
}

void Worm::jumpRight() {
    this->wormPhysic.jumpRight();
}

void Worm::jumpLeft() {
    this->wormPhysic.jumpLeft();
}

void Worm::moveRight() {
    this->wormPhysic.jumpRight();
}

void Worm::moveLeft() {
    this->wormPhysic.jumpLeft();
}

float Worm::getPosX() {
    return this->wormPhysic.getPosX();
}

float Worm::getPosY() {
    return this->wormPhysic.getPosY();
}

int Worm::getId() {
    return 1;
}

int Worm::getTeam() {
    return 2;
}

int Worm::getHealth() {
    return 100;
}

std::string Worm::getName() {
    return "Pepe";
}