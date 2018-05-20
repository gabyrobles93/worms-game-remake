#ifndef WORM_PHYSIC_H
#define WORM_PHYSIC_H

#include "Box2D.h"

#define MOVE_VELOCITY 2.0f
#define WORM_HEIGHT 0.8f
#define WORM_WIDTH 0.8f
#define WORM_DENSITY 1.0f
#define WORM_FRICTION 0.3f

class WormPhysic {
private:
    b2Body* body;
    b2World world;

public:
    WormPhysic(b2World& world, float posX, float posY);
    void jump();
    void jumpRight();
    void jumpLeft();
    void jumpFoward();
    void moveRight();
    void moveLeft();
    float getPosX();
    float getPosY();
};

#endif