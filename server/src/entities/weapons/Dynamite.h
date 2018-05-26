#ifndef DYNAMITE_H
#define DYNAMITE_H

#include "DynamitePhysic.h"
#include "Box2D/Box2D.h"

class Dynamite {
private: 
    int delay;
    DynamitePhysic dynamitePhysic;
public:
    Dynamite(b2World& world, float posX, float posY);
    void explode();
};

#endif