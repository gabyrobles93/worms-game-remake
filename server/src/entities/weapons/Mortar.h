#ifndef MORTAR_H
#define MORTAR_H

#include "Weapon.h"
#include "Box2D.h"
#include "types.h"
#include "Bazooka.h"
#include "Configuration.h"
#include "Fragment.h"

class Mortar : public Bazooka {
public:
    Mortar(int id, b2World& world, float posX, float posY, float mirrored, float shooting_angle, int power_factor, weapon_t type);
    int addProjectiles(std::map<int, Weapon*> & weapons);
};

#endif