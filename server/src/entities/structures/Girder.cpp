#include "Girder.h"

Girder::Girder(b2World& world, float posX, float posY, float angle, float height, float width) : 
world(world) {
    b2BodyDef girderDef;
    girderDef.type = b2_staticBody;
    girderDef.position.Set(posX, posY);
    girderDef.allowSleep = true;
    girderDef.angle = angle;
    b2Body* body = world.CreateBody(&girderDef);
    body->SetUserData(this);
    body->SetAwake(false);

    b2PolygonShape girderShape;
    girderShape.SetAsBox(width/2, height/2);

    b2FixtureDef girderFixture;
    girderFixture.shape = &girderShape;
    girderFixture.filter.categoryBits = STRUCTURE_PHYSIC;
    girderFixture.filter.maskBits = WORM_PHYSIC;
    if (angle <= 0.8 && angle >= -0.8) {
        girderFixture.friction = GIRDER_FRICTION;
    } else {
        girderFixture.friction = SLIPPERY_GIRDER;
    }
    girderFixture.density = GIRDER_DENSITY;

    body->CreateFixture(&girderFixture);

    this->body = body;
}

float Girder::getPosX() {
	return this->body->GetPosition().x;
}

float Girder::getPosY() {
    return this->body->GetPosition().y;
}

float Girder::getAngle() {
    return this->body->GetAngle();
}

Girder::~Girder(void) {
    this->world.DestroyBody(this->body);
}

void Girder::update() {
    this->body->SetAwake(false);
}