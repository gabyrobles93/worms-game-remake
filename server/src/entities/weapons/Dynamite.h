#ifndef DYNAMITE_H
#define DYNAMITE_H


#include "Weapon.h"
#include "Box2D/Box2D.h"
#include "types.h"
#include "Configuration.h"
#include "ExplosionManager.h"

#define DYNAMITE_WIDTH 0.1f
#define DYNAMITE_HEIGHT 0.2f

class Dynamite : public Weapon{
private: 
    int detonationTime;
    b2World& world;
    b2Body* body;
    int blast_power;
public:
    Dynamite(int id, b2World& world, float posX, float posY, int delay, int currentTime);
    ~Dynamite();
    void explode(void);
    void update(int currentTime, int wind_force);
    bool hasExploded(void);
    float getPosX(void);
    float getPosY(void);
    bool isMoving(void);
    entity_t getEntityType() {return DYNAMITE;}
};

#endif