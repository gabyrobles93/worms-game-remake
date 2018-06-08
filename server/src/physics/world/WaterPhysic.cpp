#include "WaterPhysic.h"

WaterPhysic::WaterPhysic(b2World& world, float posX, float posY, float width, float height, Entity* entity) {
    b2BodyDef waterDef;
    waterDef.type = b2_staticBody;
    waterDef.position.Set(posX, posY);
    waterDef.allowSleep = true;
    b2Body* body = world.CreateBody(&waterDef);
    body->SetUserData(entity);
    body->SetAwake(false);

    b2PolygonShape waterShape;
    waterShape.SetAsBox(width/2, height/2);

    b2FixtureDef waterFixture;
    waterFixture.shape = &waterShape;
    waterFixture.density = 1;
    waterFixture.friction = 1;
    waterFixture.filter.categoryBits = WATER_PHYSIC;
    waterFixture.filter.maskBits = WORM_PHYSIC;
    body->CreateFixture(&waterFixture);

    this->body = body;
}