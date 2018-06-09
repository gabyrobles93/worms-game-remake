#include "Grenade.h"
#include "types.h"

Grenade::Grenade(int id, b2World& world, float posX, float posY, bool mirrored, float shooting_angle, int power_factor, int delay, int currentTime, weapon_t type) :
Weapon(type),
detonationTime(currentTime + delay),
world(world) {
    b2BodyDef grenadeDef;
    grenadeDef.type = b2_dynamicBody;
    grenadeDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&grenadeDef);

    b2CircleShape grenadeShape;
    grenadeShape.m_radius = GRENADE_RADIUS;

    b2FixtureDef grenadeFixture;
    grenadeFixture.shape = &grenadeShape;
    grenadeFixture.density = GRENADE_DENSITY;
    grenadeFixture.friction = 50000000;
    grenadeFixture.restitution = gConfiguration.GRENADE_RESTITUTION;
    body->CreateFixture(&grenadeFixture);

    this->body = body;

    this->exploded = false;
    this->power_factor = power_factor;
    this->mirrored = mirrored;
    this->shooting_angle = shooting_angle;
    this->id = id;

    if (type == w_banana) {
        this->blast_power = gConfiguration.BANANA_BLAST_POWER;
        this->blast_radius = gConfiguration.BANANA_BLAST_RADIUS;
    } else if (type == w_holy_grenade) {
        this->blast_power = gConfiguration.HOLY_GRENADE_BLAST_POWER;
        this->blast_radius = gConfiguration.HOLY_GRENADE_BLAST_RADIUS;
    } else if (type == w_green_grenade) {
        this->blast_power = gConfiguration.GREEN_GRENADE_BLAST_POWER;
        this->blast_radius = gConfiguration.GREEN_GRENADE_BLAST_RADIUS;
    }
    shoot();
}

Grenade::~Grenade() {
    this->world.DestroyBody(this->body);
}

void Grenade::update(int currentTime) {
    if (currentTime >= this->detonationTime && !exploded) {
        explode();
    }
    this->countdown = this->detonationTime - currentTime;
}

void Grenade::explode() {
    ExplosionManager explosioManager(this->world);
    b2Vec2 center = this->body->GetPosition();
    explosioManager.manageExplosion(center, blast_radius, blast_power);
    this->exploded = true;
}

float Grenade::getPosX() {
    return this->body->GetPosition().x;
}

float Grenade::getPosY() {
    return this->body->GetPosition().y;
}

void Grenade::shoot() {
    float impulse = this->body->GetMass() * power_factor;
    float x_impulse = cosf(shooting_angle * gConfiguration.DEGTORAD) * impulse;
    float y_impulse = sinf(shooting_angle * gConfiguration.DEGTORAD) * impulse;
    if (!mirrored) x_impulse = x_impulse * -1;
    this->body->ApplyLinearImpulse(b2Vec2(x_impulse, -y_impulse), this->body->GetWorldCenter(), true);
}