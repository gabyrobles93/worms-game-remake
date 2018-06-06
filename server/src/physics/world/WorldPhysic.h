#ifndef WORLD_PHYSIC_H
#define WORLD_PHYSIC_H

#include "Box2D.h"
#include "ContactListener.h"
#include "Configuration.h"

class WorldPhysic {
public:
    WorldPhysic();
    b2World& getWorld();
    void step();
    void clearForces();
    bool aliveBodies();
private:
    ContactListener contactListener;
    b2Vec2 _generateGravity();
    b2World world;
};

#endif