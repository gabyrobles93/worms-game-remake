#ifndef WEAPON_H
#define WEAPON_H

#include "Entity.h"
#include "types.h"
#include <map>

class Weapon : public Entity {
public:
    virtual ~Weapon();
    virtual void update(int current_time, int wind_force) = 0;
    virtual void explode(void) = 0;
    virtual weapon_t getType(void);
    virtual bool isMoving() = 0;
    virtual int getDirectionAngle();
    virtual int addProjectiles(std::map<int, Weapon*> & weapons);
    bool hasExploded(void);
    virtual int getCountdown();
    int getBlastRadius();
    virtual int getId();
protected:
    explicit Weapon(weapon_t type);
    weapon_t type;
    bool exploded;
    bool wind_affected;
    int blast_radius;
    int countdown;
    int id;
    int direction_angle;
};

#endif