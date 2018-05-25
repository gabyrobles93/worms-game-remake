#ifndef GIRDER_H
#define GIRDER_H

#include "Box2D.h"
#include "GirderPhysic.h"
#include "Entity.h"

class Girder : public Entity {
private:
    int id;
    GirderPhysic girderPhysic;
public:
    Girder(b2World& world, float posX, float posY, float angle, float height, float width);
    virtual ~Girder(void);
    float getPosX();
    float getPosY();
    float getAngle();
    entity_t getEntityType() {return STRUCTURE;}
};

#endif