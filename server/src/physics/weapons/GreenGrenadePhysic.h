#ifndef GREEN_GRENADE_PHYSIC_H
#define GREEN_GRENADE_PHYSIC_H

#include "Box2D.h"

#define GRENADE_RADIUS 0.25f
#define GREEN_GRENADE_DENSITY 1

class GreenGrenadePhysic {
private:
    b2Body* body;
    b2World& world;
public:
    GreenGrenadePhysic(b2World& world, float posX, float posY);
    ~GreenGrenadePhysic();
};

#endif