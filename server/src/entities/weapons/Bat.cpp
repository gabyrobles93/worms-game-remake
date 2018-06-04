#include "Bat.h"
#include "types.h"

Bat::Bat(b2World& world, float posX, float posY, float angle) :
Weapon(w_bat),
batPhysic(world, posX, posY, angle, this) {

}

void Bat::atack(Worm* worm) {
    worm->hurt(BAT_DAMAGE);
}