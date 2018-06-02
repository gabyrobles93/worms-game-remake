#ifndef GREEN_GRENADE_H
#define GREEN_GRENADE_H

#include "Box2D.h"
#include "Weapon.h"
#include "GreenGrenadePhysic.h"

#define BLAST_RADIUS 2.0
#define BLAST_POWER 30
#define TIME_FACTOR 60

class GreenGrenade : public Weapon {
private:
    int delay;
    GreenGrenadePhysic greenGrenadePhysic;
public:
    GreenGrenade(b2World& world, float posX, float posY/*, float shooting_angle*/);
    void shoot(void);
    void explode(void);
    void update(void);
    bool hasExploded(void);
};

#endif