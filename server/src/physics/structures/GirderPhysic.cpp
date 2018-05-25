#include "GirderPhysic.h"

GirderPhysic::GirderPhysic(b2World& world, float posX, float posY, float height, float width, float angle) {
    b2BodyDef girderDef;
    girderDef.type = b2_staticBody;
    girderDef.position.Set(posX, posY);
    girderDef.angle = angle;
    b2Body* body = world.CreateBody(&girderDef);

    b2PolygonShape girderShape;
    girderShape.SetAsBox(width/2, height/2);

    b2FixtureDef girderFixture;
    girderFixture.shape = &girderShape;
    girderFixture.filter.categoryBits = STRUCTURE;
    girderFixture.filter.maskBits = WORM;
    if (angle <= 0.8 && angle >= -0.8) {
        girderFixture.friction = GIRDER_FRICTION;
    } else {
        girderFixture.friction = SLIPPERY_GIRDER;
    }
    girderFixture.density = GIRDER_DENSITY;

    body->CreateFixture(&girderFixture);

    this->body = body;
}

float GirderPhysic::getPosX() {
    return this->body->GetPosition().x;
}

float GirderPhysic::getPosY() {
    return this->body->GetPosition().y;
}

float GirderPhysic::getAngle() {
    return this->body->GetAngle();
}