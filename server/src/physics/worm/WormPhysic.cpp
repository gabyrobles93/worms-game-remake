#include "WormPhysic.h"

WormPhysic::WormPhysic(b2World& world, float posX, float posY) : world(world) {
    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
    wormDef.fixedRotation = true;
    wormDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&wormDef);

    b2PolygonShape wormShape;
    wormShape.SetAsBox(WORM_WIDTH/2, WORM_HEIGHT/2);

    b2FixtureDef wormFixture;
    wormFixture.shape = &wormShape;
    wormFixture.density = WORM_DENSITY;
    wormFixture.friction = WORM_FRICTION;
    wormFixture.filter.categoryBits = WORM;
    wormFixture.filter.maskBits = STRUCTURE | WATER;
    body->CreateFixture(&wormFixture);
    this->body = body;
}

void WormPhysic::moveRight() {
    b2Vec2 velocity = this->body->GetLinearVelocity();
    velocity.x = MOVE_VELOCITY;
    this->body->SetLinearVelocity(velocity);
}

void WormPhysic::moveLeft() {
    b2Vec2 velocity = this->body->GetLinearVelocity();
    velocity.x = -MOVE_VELOCITY;
    this->body->SetLinearVelocity(velocity);
}

void WormPhysic::jump() {
    float impulse = this->body->GetMass() * 5;
    this->body->ApplyLinearImpulse(b2Vec2(0, impulse), this->body->GetWorldCenter(), true);
}

void WormPhysic::frontJump() {
    float impulse = this->body->GetMass() * 5;
    this->body->ApplyLinearImpulse(b2Vec2(impulse,-impulse), this->body->GetWorldCenter(), true);
}

void WormPhysic::backJump() {
    float impulse = this->body->GetMass() * 5;
    this->body->ApplyLinearImpulse(b2Vec2(-impulse, -impulse), this->body->GetWorldCenter(), true);
}

float WormPhysic::getPosX() {
    return this->body->GetPosition().x;
}

float WormPhysic::getPosY() {
    return this->body->GetPosition().y;
}