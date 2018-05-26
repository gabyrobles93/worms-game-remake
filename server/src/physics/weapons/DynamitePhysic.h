#ifndef DYNAMITE_PHYSIC_H
#define DYNAMITE_PHYSIC_H

#include "Box2D/Box2D.h"   
//#include "RayCastClosestCallBack.h"
#include "ExplosionManager.h"

#define DYNAMITE_WIDTH 0.2f
#define DYNAMITE_HEIGHT 0.4f
#define NUM_RAYS 32
#define GRADTORAD 0.0174533
#define BLAST_RADIUS 4.0
#define BLAST_POWER 100


class DynamitePhysic {
    private:
        b2Body* body;
        b2World& world;
        //void applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower);
    public:
    DynamitePhysic(b2World& World, float posX, float posY);
    ~DynamitePhysic();
    void explode();
};

#endif
