#ifndef BAT_H
#define BAT_H

#include "Weapon.h"
#include "Box2D.h"
#include "Worm.h"
#include "types.h"
#include "Configuration.h"
#include "PhysicEntity.h"

#define BAT_WIDTH 0.2f
#define BAT_HEIGTH 0.4f

class Bat : public Weapon {
private:
    b2World& world;
    b2Body* body;
public:
    Bat(b2World& world, float posX, float posY, float angle);
    ~Bat();
    void atack(Worm* worm);
    bool isMoving(void);
};

#endif