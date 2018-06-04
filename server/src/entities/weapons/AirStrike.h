#ifndef AIR_STRIKE_H
#define AIR_STRIKE_H

#include "Weapon.h"
#include "Box2D.h"
#include "Configuration.h"
#include "types.h"

class AirStrike : public Weapon {
private:
public:
    AirStrike(int id, b2World& world, float posX, float posY);
};

#endif