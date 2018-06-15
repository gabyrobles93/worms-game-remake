#ifndef WALL_H
#define WALL_H

#include "Box2D.h"
#include "Entity.h"
#include "PhysicEntity.h"

class Wall : public Entity {
private:
    b2World& world;
    b2Body* body;
public:
    Wall(b2World& world, float posX, float posY, float width, float height);
    ~Wall();
    entity_t getEntityType() {return WALL;}
    void update(void);
    float getPosX(void);
    float getPosY(void);
};

#endif