#ifndef BAT_H
#define BAT_H

#include "Weapon.h"
#include "Box2D.h"
#include "Worm.h"
#include "types.h"
#include "Configuration.h"
#include "PhysicEntity.h"
#include "RayCastClosestCallBack.h"
#include "Entity.h"

class Bat {
private:
    b2World& world;
    float posX;
    float posY;
    bool mirrored;
    float angle;
    int rayLength;
public:
    Bat(b2World& world, float posX, float posY, bool mirrored, float angle);
    void rayCast(void);
    void atack(Worm* worm, b2Body* body);
};

#endif