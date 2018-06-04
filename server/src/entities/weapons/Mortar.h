#ifndef MORTAR_H
#define MORTAR_H

#include "Weapon.h"
#include "Box2D.h"
#include "types.h"
#include "Configuration.h"

class Mortar : public Weapon {
private:
public:
    Mortar(int id, b2World& world, float posX, float posY);
};

#endif