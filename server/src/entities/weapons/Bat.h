#ifndef BAT_H
#define BAT_H

#include "Weapon.h"
#include "Box2D.h"
#include "BatPhysic.h"
#include "Worm.h"
#include "types.h"
#include "Configuration.h"

class Bat : public Weapon {
private:
    BatPhysic batPhysic;
public:
    Bat(b2World& world, float posX, float posY, float angle);
    void atack(Worm* worm);

};

#endif