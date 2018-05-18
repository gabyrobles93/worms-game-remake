#include "WormPhysic.h"

WormPhysic::WormPhysic(b2World& world, float posX, float posY) {
    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
    wormDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&wormDef);

    b2PolygonShape wormShape;
    wormShape.SetAsBox(WORM_WIDTH/2, WORM_HEIGHT/2);

    b2FixtureDef wormFixture;
    wormFixture.shape = &wormShape;
    wormFixture.density = WORM_DENSITY;
    wormFixture.friction = WORM_FRICTION;
    body->CreateFixture(&wormFixture);
    this->body = body;
}

void WormPhysic::moveRight() {
    b2Vec2 velocity = this->body->GetLinearVelocity();
    velocity.x = -MOVE_VELOCITY;
    this->body->SetLinearVelocity(velocity);
}

void WormPhysic::moveLeft() {
    b2Vec2 velocity = this->body->GetLinearVelocity();
    velocity.y = MOVE_VELOCITY;
    this->body->SetLinearVelocity(velocity);
}

void WormPhysic::jump() {
    //TODO
}

void WormPhysic::jumpLeft() {
    //TODO
}

void WormPhysic::jumpRight() {
    //TODO
}

float WormPhysic::getPosX() {
    return this->body->GetPosition().x;
}

float WormPhysic::getPosY() {
    return this->body->GetPosition().y;
}