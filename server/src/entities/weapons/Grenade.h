#ifndef GRENADE_H
#define GRENADE_H

#include "Box2D.h"
#include "Weapon.h"
#include "types.h"
#include "Configuration.h"
#include "ExplosionManager.h"

#define GRENADE_RADIUS 0.25f
#define GRENADE_DENSITY 1

class Grenade : public Weapon {
private:    
    int detonationTime;
    b2World & world;
    b2Body* body;
    int blast_power;
    bool mirrored;
    int shooting_angle;
    int power_factor;
    void explode(void);
public:
    Grenade(int id, b2World& world, float posX, float posY, bool mirrored, float shooting_angle, int power_factor, int delay, int currentTime, weapon_t type);
    ~Grenade();
    void shoot(void);
    void update(int currentTime);
    float getPosX();
    float getPosY();
    bool isMoving();
    entity_t getEntityType() {return DYNAMITE;}
};

#endif