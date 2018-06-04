#ifndef BAZOOKA_H
#define BAZOOKA_H

#include "Weapon.h"
#include "Box2D.h"
#include "types.h"
#include "Configuration.h"

class Bazooka : public Weapon {
private:
public:
    Bazooka(int id, b2World& world, float posX, float posY);
};

#endif