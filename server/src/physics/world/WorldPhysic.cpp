#include "WorldPhysic.h"

b2Vec2 WorldPhysic::_generateGravity() {
    b2Vec2 gravity(0.0f, -10.0f);
    return gravity;
}

WorldPhysic::WorldPhysic() : world(_generateGravity()) {
}

b2World& WorldPhysic::getWorld() {
    return this->world;
}