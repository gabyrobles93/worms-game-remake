#include "Mortar.h"
#include "types.h"

Mortar::Mortar(int id, b2World& world, float posX, float posY, float mirrored, float shooting_angle, int power_factor, weapon_t type) :
Bazooka(id, world, posX, posY, mirrored, shooting_angle, power_factor, type) {

}

int Mortar::addProjectiles(std::map<int, Weapon*> & weapons) {
    for (int i = 1; i < gConfiguration.MORTAR_FRAGMENT_QUANTITY; ++i) {
        Fragment* fragment = new Fragment(this->id + i,
        this->world,
        getPosX(),
        getPosY(),
        w_air_strike);
        weapons.insert(std::pair<int, Weapon*>(fragment->getId(), fragment));
    }
    return gConfiguration.MORTAR_FRAGMENT_QUANTITY;
}