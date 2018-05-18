#ifndef GIRDER_H
#define GIRDER_H

#include "Box2D/Box2D.h"
#include "GirderPhysic.h"

class Girder {
private:
    int id;
    GirderPhysic girderPhysic;
public:
    Girder(b2World& world, float posX, float posY, float angle, float height, float width);
};

#endif