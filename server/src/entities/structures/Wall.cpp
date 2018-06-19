#include "Wall.h"

Wall::Wall(b2World& world, float posX, float posY, float width, float height) :
world(world) {
    b2BodyDef wallDef;
    wallDef.type = b2_staticBody;
    wallDef.position.Set(posX, posY);
    wallDef.allowSleep = true;
    b2Body* body = world.CreateBody(&wallDef);
    body->SetAwake(false);
    body->SetUserData(this);

    b2PolygonShape wallShape;
    wallShape.SetAsBox(width/2, height/2);

    b2FixtureDef wallFixture;
    wallFixture.shape = &wallShape;
    wallFixture.density = 1;
    wallFixture.friction = 0.3;
    wallFixture.filter.categoryBits = STRUCTURE_PHYSIC;
    wallFixture.filter.maskBits = WORM_PHYSIC;

    body->CreateFixture(&wallFixture);
    this->body = body;
}

Wall::~Wall() {
    this->world.DestroyBody(this->body);
}

void Wall::update() {
    this->body->SetAwake(false);
}

float Wall::getPosX() {
    return this->body->GetPosition().x;
}

float Wall::getPosY() {
    return this->body->GetPosition().y;
}