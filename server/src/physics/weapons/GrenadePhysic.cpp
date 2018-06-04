#include "GrenadePhysic.h"

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

void GrenadePhysic::shoot() {
    float x_impulse = this->body->GetMass() * 4;
    float y_impulse = this->body->GetMass() * 2;
    this->body->ApplyLinearImpulse(b2Vec2(x_impulse, y_impulse), this->body->GetWorldCenter(), true);
}