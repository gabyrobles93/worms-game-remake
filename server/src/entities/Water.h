#ifndef WATER_H
#define WATER_H

#include "Box2D.h"
#include "Entity.h"
#include "PhysicEntity.h"

class Water : public Entity{
private:
    b2World& world;
    b2Body* body;

public:
    Water(b2World& world, float posX, float posY, float width, float height);
    virtual ~Water();
    entity_t getEntityType() {return WATER;}
    void update(void);
    float getPosX();
    float getPosY();
};

#endif