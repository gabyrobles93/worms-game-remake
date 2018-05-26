#ifndef WATER_PHYSIC_H
#define WATER_PHYSIC_H

#include "Box2D.h"
#include "PhysicEntity.h"
#include "Entity.h"

class WaterPhysic {
private:
    b2Body* body;
public:
    WaterPhysic(b2World& world, float posX, float posY, float width, float height, Entity* entity);
};

#endif