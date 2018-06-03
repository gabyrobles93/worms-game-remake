#ifndef WEAPON_H
#define WEAPON_H

#include "Entity.h"

class Weapon : public Entity {
public:
    virtual ~Weapon();
    virtual void update(int currentTime) = 0;
    virtual void explode(void) = 0;
    bool hasExploded(void);
    virtual int getCountDown();
protected:
    bool exploded;
    int count_down;
};

#endif