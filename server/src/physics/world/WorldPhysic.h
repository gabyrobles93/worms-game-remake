#ifndef WORLD_PHYSIC_H
#define WORLD_PHYSIC_H

#include "Box2D.h"

class WorldPhysic {
public:
    WorldPhysic();
    b2World& getWorld();
private:
    b2Vec2 _generateGravity();
    b2World world;
};

#endif