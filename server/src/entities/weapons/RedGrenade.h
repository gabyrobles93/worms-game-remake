#ifndef RED_GRENADE_H
#define RED_GRENADE_H

#include "Weapon.h"
#include "Box2D.h"
#include "types.h"
#include "Configuration.h"

class RedGrenade : public Weapon {
private:
public:
    RedGrenade(int id, b2World& world, float posX, float posY);
};

#endif