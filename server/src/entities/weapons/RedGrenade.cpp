#include "RedGrenade.h"
#include "types.h"

RedGrenade::RedGrenade(int id, b2World& world, float posX, float posY, bool mirrored, float shooting_angle, int power_factor, int delay, int currentTime, weapon_t type) :
Grenade(id, world, posX, posY, mirrored, shooting_angle, power_factor, delay, currentTime, type) {
}

int RedGrenade::addProjectiles(std::map<int, Weapon*> & weapons) {
    for (int i = 1; i < gConfiguration.RED_GRENADE_FRAGMENT_QUANTITY + 1; ++i) {
        Fragment* fragment = new Fragment(this->id+i, 
        this->world, 
        getPosX(),
        getPosY(),
        w_air_strike);
        weapons.insert(std::pair<int, Weapon*>(fragment->getId(), fragment));
    }
    return gConfiguration.RED_GRENADE_FRAGMENT_QUANTITY;
}