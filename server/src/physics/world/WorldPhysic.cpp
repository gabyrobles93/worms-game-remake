#include "WorldPhysic.h"
#include <iostream>
b2Vec2 WorldPhysic::_generateGravity() {
    b2Vec2 gravity(0.0f, 9.8f);
    return gravity;
}

WorldPhysic::WorldPhysic() : world(_generateGravity()) {
    this->world.SetAllowSleeping(true);
    this->world.SetContactListener(&contactListener);
}

b2World& WorldPhysic::getWorld() {
    return this->world;
}

bool WorldPhysic::aliveBodies() {
    for (b2Body* b = this->world.GetBodyList(); b; b = b->GetNext()) {
        if (b->IsAwake()) {
            //std::cout << "LA ENTIDAD DESPIERTA ES: " << static_cast<Entity*>(b->GetUserData())->getEntityType() << std::endl;
            return true;
        }
    }
    std::cout << "ESTAN TODOS MUERTOS " << std::endl;
    return false;
}

void WorldPhysic::step() {
    this->world.Step(gConfiguration.WORLD_TIME_STEP, gConfiguration.WORLD_VELOCITY_ITERATIONS, gConfiguration.WORLD_POSITION_ITERATIONS);
}

void WorldPhysic::clearForces() {
    this->world.ClearForces();
}
