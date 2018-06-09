#ifndef ENTITY_H
#define ENTITY_H

typedef enum {
    WORM,
    STRUCTURE,
    DYNAMITE,
    BAT,
    WATER,
    BAZOOKA,
    MISSIL,
    GRENADE,
} entity_t;

class Entity {
public:
    virtual entity_t getEntityType() = 0;
    virtual float getPosX() = 0;
    virtual float getPosY() = 0;
    //virtual void update(int currentTime) = 0;
};

#endif