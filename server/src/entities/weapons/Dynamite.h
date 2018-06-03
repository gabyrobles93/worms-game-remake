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
    int detonationTime;
    DynamitePhysic dynamitePhysic;
public:
    Dynamite(int id, b2World& world, float posX, float posY, int delay, int currentTime);
    void explode(void);
    void update(int currentTime);
    bool hasExploded(void);
    float getPosX(void);
    float getPosY(void);
    entity_t getEntityType() {return DYNAMITE;}
};

#endif