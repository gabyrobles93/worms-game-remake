#include "WorldPhysic.h"

b2Vec2 WorldPhysic::_generateGravity() {
    b2Vec2 gravity(0.0f, 9.8f);
    return gravity;
}

WorldPhysic::WorldPhysic() : world(_generateGravity()) {
    this->world.SetContactListener(&contactListener);
}

b2World& WorldPhysic::getWorld() {
    return this->world;
}

void WorldPhysic::step() {
    this->world.Step(gConfiguration.WORLD_TIME_STEP, gConfiguration.WORLD_VELOCITY_ITERATIONS, gConfiguration.WORLD_POSITION_ITERATIONS);
}

void WorldPhysic::clearForces() {
    this->world.ClearForces();
}
