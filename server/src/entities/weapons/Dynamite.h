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
    int activeTime;
    DynamitePhysic dynamitePhysic;
public:
    Dynamite(b2World& world, float posX, float posY, int delay, int currentTime);
    void explode(void);
    void update(int currentTime);
    bool hasExploded(void);
    int getActiveTime();
    float getPosX(void);
    float getPosY(void);
    entity_t getEntityType() {return DYNAMITE;}
};

#endif