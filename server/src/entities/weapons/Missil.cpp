#include "Missil.h"
#include <iostream>

Missil::Missil(int id, b2World& world, float posX, float posY, weapon_t type) : 
Weapon(type),
world(world) {
    b2BodyDef missilDef;
    missilDef.type = b2_dynamicBody;
    missilDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&missilDef);
    body->SetUserData(this);

    b2PolygonShape missilShape;
    missilShape.SetAsBox(MISSIL_WIDTH/2, MISSIL_HEIGHT/2);

    b2FixtureDef missilFixture;
    missilFixture.shape = &missilShape;
    missilFixture.density = 1;
    missilFixture.friction = 0.3;

    body->CreateFixture(&missilFixture);

    this->body = body;
    this->blast_radius = gConfiguration.AIR_STRIKE_BLAST_RADIUS;
    this->blast_power = gConfiguration.AIR_STRIKE_BLAST_POWER;
    this->exploded = false;
    this->contact = false;
    this->id = id;
    this->wind_affected = true;
}

Missil::~Missil() {
    this->world.DestroyBody(this->body);
}

void Missil::explode() {
    ExplosionManager explosionManager(this->world);
    b2Vec2 center = this->body->GetPosition();
    explosionManager.manageExplosion(center, blast_radius, blast_power);
    this->exploded = true;
}

float Missil::getPosX() {
    return this->body->GetPosition().x;
}

float Missil::getPosY() {
    return this->body->GetPosition().y;
}

void Missil::update(int currentTime, int wind_force) {
    if (this->body->GetPosition().y > gConfiguration.WORLD_Y_LIMIT || contact) {
        this->explode();
    }
    
    if (wind_affected) {
        this->body->ApplyForce(body->GetMass() * b2Vec2(wind_force, 0), body->GetWorldCenter(), true);
    }

    b2Vec2 mov_speed = this->body->GetLinearVelocity();

    if (round(mov_speed.x) == 0) {
        if (mov_speed.y > 0) {
            this->direction_angle = 180;
            return;
        }

        if (mov_speed.y < 0) {
            this->direction_angle = 0;
            return;
        }
    }

    if (round(mov_speed.y) == 0) {
        if (mov_speed.x > 0) {
            this->direction_angle = 90;
            return;
        }

        if (mov_speed.x < 0) {
            this->direction_angle = 270;
            return;
        }
    }

    int ang = atan(mov_speed.x/mov_speed.y) * gConfiguration.RADTODEG;

    // Primer cuadrante
    if (mov_speed.y < 0 && mov_speed.x > 0) {
        this->direction_angle = -ang;
    }

    // Segundo cuadrante
    if (mov_speed.y < 0 && mov_speed.x < 0) {
        this->direction_angle = 360 - ang;
    }

    // Tercer cuadrante
    if (mov_speed.y > 0 && mov_speed.x < 0) {
        this->direction_angle = 180 - ang;
    }

    // Cuarto cuadrante
    if (mov_speed.y > 0 && mov_speed.x > 0) {
        this->direction_angle = 180 - ang;
    }
}

void Missil::setContact(bool made_contact) {
    this->contact = made_contact;
}

bool Missil::isMoving() {
    b2Vec2 speed = this->body->GetLinearVelocity();
    if (!speed.x && !speed.y) return false;
    return true;
}