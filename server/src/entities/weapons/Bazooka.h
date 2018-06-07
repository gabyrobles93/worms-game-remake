#ifndef BAZOOKA_H
#define BAZOOKA_H

#include "Weapon.h"
#include "Box2D.h"
#include "types.h"
#include "Configuration.h"
#include "BazookaPhysic.h"

class Bazooka : public Weapon {
private:
    int shooting_angle;
    int power_factor;
    bool mirrored;
    int blast_power;
    BazookaPhysic bazookaPhysic;
public:
    Bazooka(int id, b2World& world, float posX, float posY, float mirrored, float shooting_angle, int power_factor, weapon_t type);
    void explode(void);
    float getPosX();
    float getPosY();
    void shoot(void);
    entity_t getEntityType() {return BAZOOKA;}
    void update(int currentTime);
};

#endif