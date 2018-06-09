#include "Dynamite.h"
#include <iostream>
#include "types.h"

Dynamite::Dynamite(int id, b2World& world, float posX, float posY, int delay, int currentTime) :
Weapon(w_dynamite),
detonationTime(currentTime + delay),
world(world) {
    b2BodyDef dynamiteDef;
    dynamiteDef.type = b2_dynamicBody;
    dynamiteDef.fixedRotation = true;
    dynamiteDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&dynamiteDef);

    b2PolygonShape dynamiteShape;
    dynamiteShape.SetAsBox(0.1f, 0.2f);

    b2FixtureDef dynamiteFixture;
    dynamiteFixture.shape = &dynamiteShape;
    dynamiteFixture.density = 1;
    dynamiteFixture.friction = 1;
    body->CreateFixture(&dynamiteFixture);
    
    this->body = body;
    this->exploded = false;
    this->id = id;
    this->blast_radius = gConfiguration.DYNAMITE_BLAST_RADIUS;
    this->blast_power = gConfiguration.DYNAMITE_BLAST_POWER;
}

Dynamite::~Dynamite() {
    this->world.DestroyBody(this->body);
}

void Dynamite::update(int currentTime) {
    if (currentTime >= this->detonationTime && !exploded) {
        explode();
    }
    this->countdown = this->detonationTime - currentTime;
}

void Dynamite::explode() {
    ExplosionManager explosionManager(this->world);
    b2Vec2 center = this->body->GetPosition();
    explosionManager.manageExplosion(center, blast_radius, blast_power); 
    this->exploded = true;
}

float Dynamite::getPosX() {
    return this->body->GetPosition().x;
}

float Dynamite::getPosY() {
    return this->body->GetPosition().y;
}