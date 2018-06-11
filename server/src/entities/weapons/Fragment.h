#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "Weapon.h"
#include "Box2D.h"
#include "ExplosionManager.h"
#include "Configuration.h"
#include <stdlib.h>

#define FRAGMENT_RADIUS 0.25

class Fragment : public Weapon {
private:
    bool contact;
    int blast_power;
    b2World& world;
    b2Body* body;
    void shoot();
public: 
    Fragment(int id, b2World& world, float posX, float posY, weapon_t type);
    ~Fragment();
    void explode();
    float getPosX();
    float getPosY();
    void setContact(bool made_contact);
    bool isMoving();
    entity_t getEntityType() {return FRAGMENT;}
    void update(int currentTime, int wind_force);
};

#endif