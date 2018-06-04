#ifndef BANANA_H
#define BANANA_H

#include "Weapon.h"
#include "Box2D.h"
#include "types.h"
#include "Configuration.h"

class Banana : public Weapon {
private:
public:
    Banana(int id, b2World& world, float posX, float posY);
};

#endif