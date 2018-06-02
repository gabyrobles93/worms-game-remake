#include "DynamitePhysic.h"
#include <iostream>
DynamitePhysic::DynamitePhysic(b2World& world, float posX, float posY, int delay) : 
world(world) {
    b2BodyDef dynamiteDef;
    dynamiteDef.type = b2_dynamicBody;
    dynamiteDef.fixedRotation = true;
    dynamiteDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&dynamiteDef);

    b2PolygonShape dynamiteShape;
    dynamiteShape.SetAsBox(0.1f, 0.2f);

    b2FixtureDef dynamiteFixture;
    dynamiteFixture.shape = &dynamiteShape;
    dynamiteFixture.density = 1;
    dynamiteFixture.friction = 1;
    body->CreateFixture(&dynamiteFixture);
    this->body = body;
}

DynamitePhysic::~DynamitePhysic() {
    this->world.DestroyBody(this->body);
}

void DynamitePhysic::explode(float radius, float power) {
    ExplosionManager explosionManager(this->world);
    b2Vec2 center = this->body->GetPosition();
    explosionManager.manageExplosion(center, radius, power);  
}

