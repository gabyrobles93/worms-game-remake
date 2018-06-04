#include "WormPhysic.h"
#include <iostream>

WormPhysic::WormPhysic(b2World& world, float posX, float posY, Entity* entity) : world(world) {
    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
    wormDef.fixedRotation = true;
    wormDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&wormDef);
    body->SetUserData(entity);

    //b2PolygonShape wormShape;
    //wormShape.SetAsBox(WORM_WIDTH/2, WORM_HEIGHT/2);

    b2CircleShape wormShape;
    wormShape.m_radius = WORM_RADIUS;

    b2FixtureDef wormFixture;
    wormFixture.shape = &wormShape;
    wormFixture.density = WORM_DENSITY;
    wormFixture.friction = WORM_FRICTION;
    wormFixture.filter.categoryBits = WORM_PHYSIC;
    wormFixture.filter.maskBits = STRUCTURE_PHYSIC | WATER_PHYSIC;
    body->CreateFixture(&wormFixture);

    this->body = body;
    this->numFootContacts = 0;
}

WormPhysic::~WormPhysic() {
    this->world.DestroyBody(this->body);
}

void WormPhysic::moveRight(float angle) {
    b2Vec2 velocity = this->body->GetLinearVelocity();
    velocity.x = cosf(angle) * gConfiguration.WORM_SPEED;
    velocity.y = sinf(angle) * gConfiguration.WORM_SPEED;
    this->body->SetLinearVelocity(velocity);
}

void WormPhysic::moveLeft(float angle) {
    b2Vec2 velocity = this->body->GetLinearVelocity();
    velocity.x = cosf(angle) * -gConfiguration.WORM_SPEED;
    velocity.y = sinf(angle) * -gConfiguration.WORM_SPEED;
    this->body->SetLinearVelocity(velocity);
}

void WormPhysic::jump() {
    if (this->numFootContacts <= 0) return;
    float impulse = this->body->GetMass() * 5;
    this->body->ApplyLinearImpulse(b2Vec2(0, impulse), this->body->GetWorldCenter(), true);
}

void WormPhysic::frontJump(bool mirrored) {
    if (this->numFootContacts <= 0) return;
    float factor;
    mirrored == true ? factor = 1.0 : factor = -1.0;
    float impulse = this->body->GetMass() * 4;
    this->body->ApplyLinearImpulse(b2Vec2(impulse * factor,-impulse), this->body->GetWorldCenter(), true);
}

void WormPhysic::backJump(bool mirrored) {
    if (this->numFootContacts <= 0) return;
    float factor;
    mirrored == true ? factor = 1.0 : factor = -1.0;
    float impulse = this->body->GetMass() * 4;
    this->body->ApplyLinearImpulse(b2Vec2(-impulse * factor, -impulse), this->body->GetWorldCenter(), true);
}

float WormPhysic::getPosX() {
    return this->body->GetPosition().x;
}

float WormPhysic::getPosY() {
    return this->body->GetPosition().y;
}

void WormPhysic::addFootContact() {
    this->numFootContacts++;
}

void WormPhysic::deleteFootContact() {
    this->numFootContacts--;
}

bool WormPhysic::haveHorizontalSpeed(void) {
    b2Vec2 velocity = this->body->GetLinearVelocity();
    if (velocity.x != 0) {
        return true;
    }
    return false;
}

bool WormPhysic::haveVerticalSpeed(void) {
    b2Vec2 velocity = this->body->GetLinearVelocity();
    if (velocity.y != 0) {
        return true;
    }
    return false;
} 

bool WormPhysic::isGrounded(void) {
    return numFootContacts > 0;
}

float WormPhysic::getVerticalSpeed() {
    return this->body->GetLinearVelocity().y;
}

void WormPhysic::setPosX(float posX) {
    this->body->SetTransform(b2Vec2(posX, getPosY()), this->body->GetAngle());
}

void WormPhysic::setPosY(float posY) {
    this->body->SetTransform(b2Vec2(getPosX(), posY), this->body->GetAngle());  
}
