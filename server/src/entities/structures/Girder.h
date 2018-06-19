#ifndef GIRDER_H
#define GIRDER_H

#include "Box2D.h"
#include "PhysicEntity.h"
#include "Entity.h"
#include "Configuration.h"

#define GIRDER_DENSITY 1
#define GIRDER_FRICTION 1
#define SLIPPERY_GIRDER 0

class Girder : public Entity {
private:
    b2World& world;
    b2Body* body;
public:
    Girder(b2World& world, float posX, float posY, float angle, float height, float width);
    virtual ~Girder(void);
    float getPosX();
    float getPosY();
    float getAngle();
    entity_t getEntityType() {return STRUCTURE;}
    void update(void);
};

#endif