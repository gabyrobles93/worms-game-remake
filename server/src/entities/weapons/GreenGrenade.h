#ifndef GREEN_GRENADE_H
#define GREEN_GRENADE_H

#include "Box2D.h"
#include "Weapon.h"
#include "GreenGrenadePhysic.h"
#include "types.h"
#include "Configuration.h"

class GreenGrenade : public Weapon {
private:    
    int detonationTime;
    GreenGrenadePhysic greenGrenadePhysic;
    void explode(void);
public:
    GreenGrenade(int id, b2World& world, float posX, float posY, float shooting_angle, int power_factor, int delay, int currentTime);
    void shoot(void);
    void update(int currentTime);
    bool hasExploded(void);
    float getPosX();
    float getPosY();
};

#endif