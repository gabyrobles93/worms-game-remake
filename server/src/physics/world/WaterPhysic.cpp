#include "WaterPhysic.h"

WaterPhysic::WaterPhysic(b2World& world, float posX, float posY, float width, float height) {
    b2BodyDef waterDef;
    waterDef.type = b2_staticBody;
    waterDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&waterDef);

    b2PolygonShape waterShape;
    waterShape.SetAsBox(width/2, height/2);

    b2FixtureDef waterFixture;
    waterFixture.shape = &waterShape;
    waterFixture.density = 1;
    waterFixture.friction = 1;
    waterFixture.filter.categoryBits = WATER;
    waterFixture.filter.maskBits = WORM;
    body->CreateFixture(&waterFixture);

    this->body = body;
}