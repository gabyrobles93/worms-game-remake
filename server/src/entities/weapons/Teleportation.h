#ifndef TELEPORT_H
#define TELEPORT_H

#include "Weapon.h"
#include "Worm.h"
#include "types.h"

class Teleportation {
private:
    Worm* worm;
    float posX;
    float posY;

public:
    Teleportation(Worm* worm, float posX, float posY);
    void teleport(void);
};

#endif