#ifndef HOLY_GRENADE_H
#define HOLY_GRENADE_H

#include "Weapon.h"
#include "Box2D.h"
#include "types.h"
#include "Configuration.h"

class HolyGrenade : public Weapon {
private:
public:
    HolyGrenade(int id, b2World& world, float posX, float posY);
};

#endif