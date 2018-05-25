#ifndef WORLD_PHYSIC_H
#define WORLD_PHYSIC_H

#include "Box2D.h"
#include "ContactListener.h"

#define VELOCITY_ITERATIONS 6
#define POSITION_ITERATIONS 2
#define TIME_STEP 1.0f/60.0f

class WorldPhysic {
public:
    WorldPhysic();
    b2World& getWorld();
    void step();
    void clearForces();
private:
    ContactListener contactListener;
    b2Vec2 _generateGravity();
    b2World world;
};

#endif