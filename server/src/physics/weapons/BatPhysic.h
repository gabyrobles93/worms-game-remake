#ifndef BAT_PHYSIC_H
#define BAT_PHYSIC_H

#include "Box2D.h"
#include "PhysicEntity.h"
#include "Entity.h"

#define BAT_WIDTH 0.2f
#define BAT_HEIGTH 0.4f

class BatPhysic {
private:
    b2Body* body;
    b2World& world;

public:
    BatPhysic(b2World& world, float posX, float posY, float angle, Entity* entity);
    ~BatPhysic();

};

#endif