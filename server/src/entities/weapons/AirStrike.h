#ifndef AIR_STRIKE_H
#define AIR_STRIKE_H

//#include "Weapon.h"
#include "Box2D.h"
#include "Configuration.h"
#include "types.h"
#include "Missil.h"

class AirStrike {
private:
    b2World& world;
    std::vector<Missil*> missils;
    float deploy_x;
    float deploy_y;
    int id;
    void createMissils();
public:
    AirStrike(int id, b2World& world, float posX, float posY);
    ~AirStrike();
    std::vector<Missil*> getMissils();
};

#endif