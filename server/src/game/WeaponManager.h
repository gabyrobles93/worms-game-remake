#ifndef WEAPON_MANGER_H
#define WEAPON_MANGER_H

#include "Weapon.h"
#include "WorldPhysic.h"
#include "types.h"
#include "Worm.h"
#include "event.h"
#include "Dynamite.h"
#include "Bazooka.h"
#include "AirStrike.h"
#include "Bat.h"
#include "Teleportation.h"
#include "RedGrenade.h"
#include "Mortar.h"
#include "Missil.h"
#include "team.h"
#include <map>
#include <iostream>

class WeaponManager {
private:
    std::map<int, Weapon*> weapons;
    std::map<int, Worm*> & worms;
    WorldPhysic & world;    
    std::map<int, Team*> & teams;

    int weaponCounter;
public: 
    WeaponManager(std::map<int, Worm*> & , std::map<int, Team*> &, WorldPhysic &);
    void manageShoot(Event & event, size_t id, unsigned int currentTime);
    void updateWeapons(unsigned int currentTime, int windForce);
    std::map<int, Weapon*> & getWeapons();
    bool hasAliveWeapons();
};

#endif