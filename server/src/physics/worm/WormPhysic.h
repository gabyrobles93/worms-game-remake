#ifndef WORM_PHYSIC_H
#define WORM_PHYSIC_H

#include "Box2D/Box2D.h"
#include "PhysicEntity.h"
#include "Entity.h"

#define MOVE_VELOCITY 2.0f
#define WORM_HEIGHT 0.8f
#define WORM_WIDTH 0.8f
#define WORM_DENSITY 1.0f
#define WORM_FRICTION 0.3f

class WormPhysic {
private:
    b2Body* body;
    b2World& world;
    int numFootContacts;

public:
    WormPhysic(b2World& world, float posX, float posY, Entity* entity);
    ~WormPhysic();
    void jump();
    void setAngle(float angle);
    void frontJump(bool);
    void backJump(bool);
    void jumpFoward();
    void moveRight();
    void moveLeft();
    float getPosX();
    float getPosY();
    void addFootContact();
    void deleteFootContact();
    bool haveHorizontalSpeed(void);
    bool haveVerticalSpeed(void);
    bool isGrounded(void);
};

#endif