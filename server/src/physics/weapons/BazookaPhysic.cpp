#include "BazookaPhysic.h"
#include <iostream>

BazookaPhysic::BazookaPhysic(b2World& world, float posX, float posY, Entity* entity) :
world(world) {
    b2BodyDef bazookaDef;
    bazookaDef.type = b2_dynamicBody;
    bazookaDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&bazookaDef);
    body->SetUserData(entity);

    b2PolygonShape bazookaShape;
    bazookaShape.SetAsBox(BAZOOKA_WIDTH/2, BAZOKOA_HEIGHT/2);

    b2FixtureDef bazookaFixture;
    bazookaFixture.shape = &bazookaShape;
    bazookaFixture.density = 1;
    bazookaFixture.friction = 0.3;
    //bazookaFixture.filter.categoryBits = BAZOOKA_PHYSIC;
    //bazookaFixture.filter.maskBits = STRUCTURE_PHYSIC | WORM_PHYSIC;
    body->CreateFixture(&bazookaFixture);
    this->body = body;
}

BazookaPhysic::~BazookaPhysic() {
    this->world.DestroyBody(this->body);
}

void BazookaPhysic::explode(float radius, float power) {
    ExplosionManager explosionManager(this->world);
    b2Vec2 center = this->body->GetPosition();
    explosionManager.manageExplosion(center, radius, power);
}

float BazookaPhysic::getPosX() {
    return this->body->GetPosition().x;
}

float BazookaPhysic::getPosY() {
    return this->body->GetPosition().y;
}

void BazookaPhysic::shoot(bool mirrored, float shooting_angle, int power_factor) {
    float impulse = this->body->GetMass() * power_factor;
    float x_impulse = impulse * cosf(shooting_angle * gConfiguration.DEGTORAD);
    float y_impulse = impulse * sinf(shooting_angle * gConfiguration.DEGTORAD);
    if (!mirrored) x_impulse = x_impulse * -1;
    this->body->ApplyLinearImpulse(b2Vec2(x_impulse, -y_impulse), this->body->GetWorldCenter(), true);
}