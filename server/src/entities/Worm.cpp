#include "Worm.h"
#include <iostream>

Worm::Worm(std::string n, int id, int team_id, int h, b2World& world, float posX, float posY) : 
wormPhysic(world, posX, posY, this),
world(world) {
    this->id = id;
    this->health = h;
    this->team_id = team_id;
    this->name = n;
    this->angle = 0;
    this->sight_angle = 0;
    this->falling = false;
    this->mirrored = false;
    this->affectedByExplosion = false;
}

Worm::~Worm(void) {

}

void Worm::jump(void) {
    this->wormPhysic.jump();
}

void Worm::frontJump(void) {
    this->wormPhysic.frontJump(this->mirrored);
}

void Worm::backJump(void) {
    this->wormPhysic.backJump(this->mirrored);
}

void Worm::moveRight(void) {
    if (isGrounded() && !affectedByExplosion) {
        this->wormPhysic.moveRight(this->angle);
        this->mirrored = true;
    }
}

void Worm::moveLeft(void) {
    if (isGrounded() && !affectedByExplosion) {
        this->wormPhysic.moveLeft(this->angle);
        this->mirrored = false;
    }
}

void Worm::pointHigher(void) {
    if (this->sight_angle < 90) {
        this->sight_angle++;
    }
}

void Worm::pointMoreDown(void) {
    if (this->sight_angle > -90) {
        this->sight_angle--;
    }
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

float Worm::getSightAngle(void) {
    return this->sight_angle;
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

void Worm::shoot(/* entity_t weapon */) {
    // switch(weapon) {
    //     case DYNAMITE : {
    //         Dynamite dynamite(this->world, posX, posY);
    //         dynamite.explode();
    //         break;
    //     }
    //     default: break;
    // }
}

void Worm::hurt(int damage) {
    if (this->getHealth() - damage < 0) {
        this->health = 0;
    } else {
        this->health -= damage;
    }
}

bool Worm::isWalking(void) {
    if (this->wormPhysic.haveVerticalSpeed()) {
        return false;
    }
    return this->wormPhysic.haveHorizontalSpeed();
}

bool Worm::isFalling(void) {
    if (this->wormPhysic.haveHorizontalSpeed()) {
        return false;
    }
    return this->wormPhysic.haveVerticalSpeed();
}

bool Worm::isGrounded(void) {
    return this->wormPhysic.isGrounded();
}

bool Worm::isDead(void) {
    return this->health == 0;
}

void Worm::setAngle(float angle) {
    this->angle = angle;
}

void Worm::setFalling(bool falling) {
    this->falling = falling;
}

void Worm::update() {
    /* float verticalSpeed = this->wormPhysic.getVerticalSpeed(); */
    if (!this->isGrounded()) {
        if (this->falled && (getPosY() < this->fallenDistance)) {
            this->fallenDistance = getPosY();
        } else if (!this->falled){
            this->fallenDistance = getPosY();
            this->falled = true;
        }
    } else if (isGrounded() && (falled)) {
        this->fallenDistance = getPosY() - this->fallenDistance; 
        if (this->fallenDistance > 2) {
            hurt(this->fallenDistance);
        }
        this->falled = false;
        this->fallenDistance = 0;
    }

    if (!this->wormPhysic.haveVerticalSpeed() && !this->wormPhysic.haveHorizontalSpeed()) {
        this->affectedByExplosion = false;
    }
}

void Worm::setPosX(float posX) {
    this->wormPhysic.setPosX(posX);
}

void Worm::setPosY(float posY) {
    this->wormPhysic.setPosX(posY);
}

void Worm::setAffectedByExplosion(){
    this->affectedByExplosion = true;
}