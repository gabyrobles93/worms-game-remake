#ifndef DYNAMITE_H
#define DYNAMITE_H

#include "DynamitePhysic.h"
#include "Weapon.h"
#include "Box2D/Box2D.h"

#define BLAST_RADIUS 4.0
#define BLAST_POWER 50
#define TIME_FACTOR 60

class Dynamite : public Weapon{
private: 
    int delay;
    DynamitePhysic dynamitePhysic;
public:
    Dynamite(b2World& world, float posX, float posY, int delay);
    void explode(void);
    void update(void);
    bool hasExploded(void);
    entity_t getEntityType() {return DYNAMITE;}
};

#endif