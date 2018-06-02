#ifndef ENTITY_H
#define ENTITY_H

typedef enum {
    WORM,
    STRUCTURE,
    DYNAMITE,
    BAT,
    WATER,
} entity_t;

class Entity {
public:
    virtual entity_t getEntityType() = 0;
    virtual void update(void) = 0;
};

#endif