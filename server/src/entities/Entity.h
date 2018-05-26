#ifndef ENTITY_H
#define ENTITY_H

typedef enum {
    WORM,
    STRUCTURE,
    DYNAMITE,
    WATER,
} entity_t;

class Entity {
public:
    virtual entity_t getEntityType() = 0;
};

#endif