#ifndef DYNAMITE_PHYSIC_H
#define DYNAMITE_PHYSIC_H

#include "Box2D/Box2D.h"   
#include "ExplosionManager.h"

#define DYNAMITE_WIDTH 0.2f
#define DYNAMITE_HEIGHT 0.4f
#define GRADTORAD 0.0174533

class DynamitePhysic {
private:
        b2Body* body;
        b2World& world;
public:
    DynamitePhysic(b2World& World, float posX, float posY,int delay);
    ~DynamitePhysic();
    void explode(float radius, float power);
};

#endif
