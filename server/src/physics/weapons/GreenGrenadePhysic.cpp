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