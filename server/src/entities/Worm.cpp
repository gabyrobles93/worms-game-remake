#include "Worm.h"
// AGREGAR EL HEALTH DE LOS GUSANOS
Worm::Worm(std::string n, bool mirrored, int id, int tid, int h, b2World& world, float posX, float posY) : wormPhysic(world, posX, posY, this) {
    this->id = id;
    this->team_id = tid;
    this->health = h;
    this->name = n;
    this->mirrored = mirrored;
    this->foot_contact = 0;
}

Worm::~Worm(void) {

}

void Worm::jump(void) {
    this->wormPhysic.jump();
}

void Worm::frontJump(void) {
    this->wormPhysic.frontJump();
}

void Worm::backJump(void) {
    this->wormPhysic.backJump();
}

void Worm::moveRight(void) {
    this->wormPhysic.moveRight();
    this->mirrored = true;
}

void Worm::moveLeft(void) {
    this->wormPhysic.moveLeft();
    this->mirrored = false;
}

bool Worm::isMirrored(void) {
    return this->mirrored;
}

float Worm::getPosX(void) {
    return this->wormPhysic.getPosX();
}

float Worm::getPosY(void) {
    return this->wormPhysic.getPosY();
}

int Worm::getId(void) {
    return this->id;
}

int Worm::getTeam(void) {
    return this->team_id;
}

int Worm::getHealth(void) {
    return this->health;
}

std::string Worm::getName(void) {
    return this->name;
}

void Worm::addFootContact(void) {
    this->wormPhysic.addFootContact();
}

void Worm::deleteFootContact(void) {
    this->wormPhysic.deleteFootContact();
}

void Worm::hurt(int damage) {
    if (this->getHealth() - damage < 0) {
        this->health = 0;
    } else {
        this->health -= damage;
    }
}