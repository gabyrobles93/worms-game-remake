#include "GreenGrenadePhysic.h"

GreenGrenadePhysic::GreenGrenadePhysic(b2World& world, float posX, float posY) :
world(world) {
    b2BodyDef greenGrenadeDef;
    greenGrenadeDef.type = b2_dynamicBody;
    greenGrenadeDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&greenGrenadeDef);

    b2CircleShape greenGrenadeShape;
    greenGrenadeShape.m_radius = GRENADE_RADIUS;

    b2FixtureDef greenGrenadeFixture;
    greenGrenadeFixture.shape = &greenGrenadeShape;
    greenGrenadeFixture.density = GREEN_GRENADE_DENSITY;
    body->CreateFixture(&greenGrenadeFixture);

    this->body = body;
}

GreenGrenadePhysic::~GreenGrenadePhysic() {
    this->world.DestroyBody(this->body);
}

void GreenGrenadePhysic::explode(float radius, float power) {
    ExplosionManager explosioManager(this->world);
    b2Vec2 center = this->body->GetPosition();
    explosioManager.manageExplosion(center, radius, power);
}

float GreenGrenadePhysic::getPosX() {
    return this->body->GetPosition().x;
}

float GreenGrenadePhysic::getPosY() {
    return this->body->GetPosition().y;
}

void GreenGrenadePhysic::shoot() {
    float x_impulse = this->body->GetMass() * 4;
    float y_impulse = this->body->GetMass() * 2;
    this->body->ApplyLinearImpulse(b2Vec2(x_impulse, y_impulse), this->body->GetWorldCenter(), true);
}