#ifndef WATER_H
#define WATER_H

#include "Box2D.h"
#include "WaterPhysic.h"

class Water {
private:
    WaterPhysic waterPhysic;
public:
    Water(b2World& world, float posX, float posY, float width, float height);
};

#endif