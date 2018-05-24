#include "Worm.h"
// AGREGAR EL HEALTH DE LOS GUSANOS
Worm::Worm(std::string n, int id, int tid, int h, b2World& world, float posX, float posY) : wormPhysic(world, posX, posY) {
    this->id = id;
    this->team_id = tid;
    this->health = h;
    this->name = n;
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
    return this->id;
}

int Worm::getTeam() {
    return this->team_id;
}

int Worm::getHealth() {
    return this->health;
}

std::string Worm::getName() {
    return this->name;
}