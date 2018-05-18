#ifndef GIRDER_PHYSIC_H
#define GIRDER_PHYSIC_H

#define GIRDER_DENSITY 1
#define GIRDER_FRICTION 0

#include "Box2D/Box2D.h"

class GirderPhysic {
private:
    b2Body* body;
public:
    GirderPhysic(b2World& world, float posX, float posY, float height, float width, float angle);

};

#endif