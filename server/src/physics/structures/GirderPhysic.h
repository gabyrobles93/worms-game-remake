#ifndef GIRDER_PHYSIC_H
#define GIRDER_PHYSIC_H

#define GIRDER_DENSITY 1
#define GIRDER_FRICTION 5
#define SLIPPERY_GIRDER 0

#include "Box2D.h"
#include "PhysicEntity.h"
#include "Entity.h"

class GirderPhysic {
private:
    b2Body* body;
public:
    GirderPhysic(b2World& world, float posX, float posY, float height, float width, float angle, Entity* entity);
    float getPosX();
    float getPosY();
    float getAngle();
    void sleep();

};

#endif