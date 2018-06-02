#ifndef WEAPON_H
#define WEAPON_H

#include "Entity.h"

class Weapon : public Entity {
public:
    virtual ~Weapon();
    virtual void update(void) = 0;
    virtual void explode(void) = 0;
    bool hasExploded(void);
protected:
    bool exploded;
};

#endif