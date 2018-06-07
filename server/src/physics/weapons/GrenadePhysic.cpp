#include "GrenadePhysic.h"
#include <iostream>

GrenadePhysic::GrenadePhysic(b2World& world, float posX, float posY) :
world(world) {
    b2BodyDef grenadeDef;
    grenadeDef.type = b2_dynamicBody;
    grenadeDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&grenadeDef);

    b2CircleShape grenadeShape;
    grenadeShape.m_radius = GRENADE_RADIUS;

    b2FixtureDef grenadeFixture;
    grenadeFixture.shape = &grenadeShape;
    grenadeFixture.density = GRENADE_DENSITY;
    grenadeFixture.friction = 50000000;
    grenadeFixture.restitution = gConfiguration.GRENADE_RESTITUTION;
    body->CreateFixture(&grenadeFixture);

    this->body = body;
}

GrenadePhysic::~GrenadePhysic() {
    this->world.DestroyBody(this->body);
}

void GrenadePhysic::explode(float radius, float power) {
    ExplosionManager explosioManager(this->world);
    b2Vec2 center = this->body->GetPosition();
    explosioManager.manageExplosion(center, radius, power);
}

float GrenadePhysic::getPosX() {
    return this->body->GetPosition().x;
}

float GrenadePhysic::getPosY() {
    return this->body->GetPosition().y;
}

void GrenadePhysic::shoot(bool mirrored, float shooting_angle) {
    std::cout << "SHOOTING ANGLE: " << shooting_angle << std::endl;
    
    float impulse = this->body->GetMass() * 10;
    float x_impulse = cosf(shooting_angle * gConfiguration.DEGTORAD) * impulse;
    float y_impulse = sinf(shooting_angle * gConfiguration.DEGTORAD) * impulse;
    //float x_impulse = this->body->GetMass() * 5;
    if (!mirrored) x_impulse = x_impulse * -1;
    //float y_impulse = this->body->GetMass() * 10;
    this->body->ApplyLinearImpulse(b2Vec2(x_impulse, -y_impulse), this->body->GetWorldCenter(), true);
}