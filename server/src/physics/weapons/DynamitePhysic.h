#ifndef DYNAMITE_PHYSIC_H
#define DYNAMITE_PHYSIC_H

#include "Box2D/Box2D.h"

#define DYNAMITE_WIDTH 0.2f;
#define DYNAMITE_HEIGHT 0.4f;

class DynamitePhysic {
    private:
        b2Body* body;
        void applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower);
    public:
    DynamitePhysic(b2World& World, float posX, float posY);
    void explode();
};

#endif
