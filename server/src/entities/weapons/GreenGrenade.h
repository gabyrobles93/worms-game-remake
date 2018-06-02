#ifndef GREEN_GRENADE_H
#define GREEN_GRENADE_H

#include "Weapon.h"

class GreenGrenade : public Weapon {
private:
public:
    GreenGrenade();
    void shoot();
    void explode();
};

#endif