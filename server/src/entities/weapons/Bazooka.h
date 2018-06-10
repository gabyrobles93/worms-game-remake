#ifndef BAZOOKA_H
#define BAZOOKA_H

#include "Weapon.h"
#include "Box2D.h"
#include "types.h"
#include "Configuration.h"
#include "ExplosionManager.h"

#define BAZOOKA_WIDTH 0.7f
#define BAZOKOA_HEIGHT 0.2f

class Bazooka : public Weapon {
private:
    b2World& world;
    b2Body* body;
    int shooting_angle;
    int power_factor;
    bool mirrored;
    bool contact;
    int blast_power;
public:
    Bazooka(int id, b2World& world, float posX, float posY, float mirrored, float shooting_angle, int power_factor, weapon_t type);
    ~Bazooka();
    void explode(void);
    float getPosX();
    float getPosY();
    void setContact(bool made_contact);
    void shoot(void);
    bool isMoving(void);
    entity_t getEntityType() {return BAZOOKA;}
    void update(int currentTime, int wind_force);
};

#endif