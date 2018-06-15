#include "Fragment.h"

Fragment::Fragment(int id, b2World& world, float posX, float posY, weapon_t type) : 
Weapon(type),
world(world) {
    b2BodyDef fragmentDef;
    fragmentDef.type = b2_dynamicBody;
    fragmentDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&fragmentDef);
    body->SetUserData(this);

    b2CircleShape fragmentShape;
    fragmentShape.m_radius = FRAGMENT_RADIUS;

    b2FixtureDef fragmentFixture;
    fragmentFixture.shape = &fragmentShape;
    fragmentFixture.density = 1;
    fragmentFixture.friction = 0.3;

    body->CreateFixture(&fragmentFixture);

    this->body = body;
    this->blast_radius = gConfiguration.AIR_STRIKE_BLAST_RADIUS;
    this->blast_power = gConfiguration.AIR_STRIKE_BLAST_POWER;
    this->exploded = false;
    this->id = id;
    this->wind_affected = true;
    shoot();
}

Fragment::~Fragment() {
    this->world.DestroyBody(this->body);
}

void Fragment::explode() {
    ExplosionManager explosionManager(this->world);
    b2Vec2 center = this->body->GetPosition();
    explosionManager.manageExplosion(center, blast_radius, blast_power);
    this->exploded = true;
}

float Fragment::getPosX() {
    return this->body->GetPosition().x;
}

float Fragment::getPosY() {
    return this->body->GetPosition().y;
}

void Fragment::update(int currentTime, int wind_force) {
    if (this->body->GetPosition().y > gConfiguration.WORLD_Y_LIMIT /*|| contact*/) {
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

bool Fragment::isMoving() {
    b2Vec2 speed = this->body->GetLinearVelocity();
    if (!speed.x && !speed.y) return false;
    return true;
}

void Fragment::shoot() {
    float impulse = this->body->GetMass() * 7;
    int angle = rand()%(181);
    float x_impulse = cosf(angle * gConfiguration.DEGTORAD) * impulse;
    float y_impulse = sinf(angle * gConfiguration.DEGTORAD) * impulse;
    this->body->ApplyLinearImpulse(b2Vec2(x_impulse, -y_impulse), this->body->GetWorldCenter(), true);
}