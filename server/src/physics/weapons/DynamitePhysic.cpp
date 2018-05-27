#include "DynamitePhysic.h"
#include <iostream>
DynamitePhysic::DynamitePhysic(b2World& world, float posX, float posY, int delay) : 
world(world),
delay(delay * TIME_FACTOR){
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
    this->exploded = false;
}

DynamitePhysic::~DynamitePhysic() {
    this->world.DestroyBody(this->body);
}

void DynamitePhysic::update() {
    if (this->delay == 0 && !exploded) {
        explode();
    } else this->delay--;
}

void DynamitePhysic::explode() {
    ExplosionManager explosionManager(this->world);
    b2Vec2 center = this->body->GetPosition();
    explosionManager.manageExplosion(center, BLAST_RADIUS, BLAST_POWER);  
    this->exploded = true;  
}

bool DynamitePhysic::hasExploded() {
    return this->exploded;
}

