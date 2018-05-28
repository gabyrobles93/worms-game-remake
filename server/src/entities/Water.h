#ifndef WATER_H
#define WATER_H

#include "Box2D.h"
#include "WaterPhysic.h"
#include "Entity.h"

class Water : public Entity{
private:
    WaterPhysic waterPhysic;
public:
    Water(b2World& world, float posX, float posY, float width, float height);
    entity_t getEntityType() {return WATER;}
    void update(void);
};

#endif