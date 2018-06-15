#ifndef EXPLOSION_MANAGER_H
#define EXPLOSION_MANAGER_H

#define GRADTORAD 0.0174533
#define REDUCE_FACTOR 5

#include "Box2D.h"
#include "Entity.h"
#include "Worm.h"
#include "QueryCallback.h"

class ExplosionManager {
private:
    b2World& world;
    void applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower);
public:
    ExplosionManager(b2World& world);
    void manageExplosion(b2Vec2 center, float radius, float power);
    
};

#endif