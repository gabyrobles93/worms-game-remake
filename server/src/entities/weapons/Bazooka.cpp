#include "Bazooka.h"
#include "types.h"
#include <iostream>

Bazooka::Bazooka(int id, b2World& world, float posX, float posY, float mirrored, 
float shooting_angle, int power_factor, weapon_t type) : 
Weapon(type),
world(world) {
    b2BodyDef bazookaDef;
    bazookaDef.type = b2_dynamicBody;
    bazookaDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&bazookaDef);
    body->SetUserData(this);

    b2PolygonShape bazookaShape;
    bazookaShape.SetAsBox(BAZOOKA_WIDTH/2, BAZOKOA_HEIGHT/2);

    b2FixtureDef bazookaFixture;
    bazookaFixture.shape = &bazookaShape;
    bazookaFixture.density = 1;
    bazookaFixture.friction = 0.3;
    //bazookaFixture.filter.categoryBits = BAZOOKA_PHYSIC;
    //bazookaFixture.filter.maskBits = STRUCTURE_PHYSIC | WORM_PHYSIC;
    body->CreateFixture(&bazookaFixture);
    this->body = body;

    this->exploded = false;
    this->power_factor = power_factor;
    this->mirrored = mirrored;
    this->shooting_angle = shooting_angle;
    this->id = id;
    this->contact = false;
    this->blast_power = gConfiguration.BAZOOKA_BLAST_POWER;
    this->blast_radius = gConfiguration.BAZOOKA_BLAST_RADIUS;
    shoot();
}

Bazooka::~Bazooka() {
    this->world.DestroyBody(this->body);
}

void Bazooka::explode() {
    ExplosionManager explosionManager(this->world);
    b2Vec2 center = this->body->GetPosition();
    explosionManager.manageExplosion(center, blast_radius, blast_power);
    this->exploded = true;
}

float Bazooka::getPosX() {
    return this->body->GetPosition().x;
}

float Bazooka::getPosY() {
    return this->body->GetPosition().y;
}

void Bazooka::shoot() {
    float impulse = this->body->GetMass() * power_factor;
    float x_impulse = impulse * cosf(shooting_angle * gConfiguration.DEGTORAD);
    float y_impulse = impulse * sinf(shooting_angle * gConfiguration.DEGTORAD);
    if (!mirrored) x_impulse = x_impulse * -1;
    this->body->ApplyLinearImpulse(b2Vec2(x_impulse, -y_impulse), this->body->GetWorldCenter(), true);
}

void Bazooka::update(int currenTime) {
    if (getPosY() > gConfiguration.WORLD_Y_LIMIT || contact) {
        this->explode();
    }
}

void Bazooka::setContact(bool made_contact) {
    this->contact = made_contact;
}

bool Bazooka::isMoving() {
    b2Vec2 speed = this->body->GetLinearVelocity();
    if (!speed.x && !speed.y) return false;
    return true;
}

