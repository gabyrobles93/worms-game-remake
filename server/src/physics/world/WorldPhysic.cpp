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

void WorldPhysic::step() {
    this->world.Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}

void WorldPhysic::clearForces() {
    this->world.ClearForces();
}