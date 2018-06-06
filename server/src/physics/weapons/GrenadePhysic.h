#ifndef GRENADE_PHYSIC_H
#define GRENADE_PHYSIC_H

#include "Box2D.h"
#include "ExplosionManager.h"
#include "Configuration.h"

#define GRENADE_RADIUS 0.25f
#define GRENADE_DENSITY 1

class GrenadePhysic {
private:
    b2Body* body;
    b2World& world;
public:
    GrenadePhysic(b2World& world, float posX, float posY);
    ~GrenadePhysic();
    void explode(float radius, float power);
    void shoot(bool mirrored, float shooting_angle);
    float getPosX();
    float getPosY();
};

#endif