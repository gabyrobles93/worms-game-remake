#include "Bat.h"

Bat::Bat(b2World& world, float posX, float posY, float angle) :
batPhysic(world, posX, posY, angle, this) {

}

void Bat::atack(Worm* worm) {
    worm->hurt(gConfiguration.BAT_DAMAGE);
}