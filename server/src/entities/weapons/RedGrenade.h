#ifndef RED_GRENADE_H
#define RED_GRENADE_H

#include "Weapon.h"
#include "Box2D.h"
#include "types.h"
#include "Configuration.h"
#include "Grenade.h"
#include "ExplosionManager.h"
#include <list>
#include "Fragment.h"
#include <map>

class RedGrenade : public Grenade {
public:
    RedGrenade(int id, b2World& world, float posX, float posY, bool mirrored, float shooting_angle, int power_factor, int delay, int currentTime, weapon_t type);
    int addProjectiles(std::map<int, Weapon*> & weapons);
};

#endif