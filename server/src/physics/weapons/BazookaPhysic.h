#ifndef BAZOOKA_PHYSIC_H
#define BAZOOKA_PHYSIC_H

#include "Box2D.h"
#include "ExplosionManager.h"
#include "Configuration.h"
#include "PhysicEntity.h"
#include "Entity.h"

#define BAZOOKA_WIDTH 0.7f
#define BAZOKOA_HEIGHT 0.2f

class BazookaPhysic {
private:
    b2Body* body;
    b2World& world;
public:
    BazookaPhysic(b2World& world, float posX, float posY, Entity* entity);
    ~BazookaPhysic();
    void explode(float radius, float power);
    void shoot(bool mirrored, float shooting_angle);
    float getPosX();
    float getPosY();
};

#endif