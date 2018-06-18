#include "Worm.h"
#include <iostream>

Worm::Worm(std::string n, int id, int team_id, int h, b2World& world, float posX, float posY) : 
world(world) {

    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
    wormDef.fixedRotation = true;
    wormDef.allowSleep = true;
    wormDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&wormDef);
    body->SetUserData(this);

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


    this->id = id;
    this->inclination = NONE;
    this->health = h;
    this->team_id = team_id;
    this->name = n;
    this->angle = 0;
    this->falling = false;
    this->mirrored = false;
    this->hurtInTurn = false;
    this->affectedByExplosion = false;
    this->shootedInTurn = false;
    this->weapon = w_null;
}

Worm::~Worm(void) {
    this->world.DestroyBody(this->body);
}

void Worm::frontJump(void) {
    if (this->numFootContacts <= 0) return;
    float factor;
    mirrored == true ? factor = 1.0 : factor = -1.0;
    float impulse = this->body->GetMass() * gConfiguration.WORM_JUMP_IMPULSE;
    this->body->ApplyLinearImpulse(b2Vec2(impulse * factor,-impulse), this->body->GetWorldCenter(), true);
}

void Worm::backJump(void) {
    if (this->numFootContacts <= 0) return;
    float factor;
    mirrored == true ? factor = 1.0 : factor = -1.0;
    float impulse = this->body->GetMass() * gConfiguration.WORM_JUMP_IMPULSE;
    this->body->ApplyLinearImpulse(b2Vec2(-impulse * factor, -impulse), this->body->GetWorldCenter(), true);
}

void Worm::moveRight(void) {
    if (isGrounded() && !affectedByExplosion) {
        b2Vec2 velocity;
        velocity.x = cosf(angle) * gConfiguration.WORM_SPEED;
        velocity.y = sinf(angle) * gConfiguration.WORM_SPEED;
        this->body->SetLinearVelocity(velocity);
        this->mirrored = true;
    }
}

void Worm::moveLeft(void) {
    if (isGrounded() && !affectedByExplosion) {
        b2Vec2 velocity; // = this->body->GetLinearVelocity();
        velocity.x = cosf(angle) * -gConfiguration.WORM_SPEED;
        velocity.y = sinf(angle) * -gConfiguration.WORM_SPEED;
        this->body->SetLinearVelocity(velocity);
        this->mirrored = false;
    }
}

bool Worm::isMirrored(void) {
    return this->mirrored;
}

float Worm::getPosX(void) {
    return this->body->GetPosition().x;
}

float Worm::getPosY(void) {
    return this->body->GetPosition().y;
}

int Worm::getId(void) {
    return this->id;
}

int Worm::getTeam(void) {
    return this->team_id;
}

int Worm::getHealth(void) {
    return this->health;
}

std::string Worm::getName(void) {
    return this->name;
}

void Worm::addFootContact(void) {
    this->numFootContacts++;
}

void Worm::deleteFootContact(void) {
    this->numFootContacts--;
}

void Worm::shoot() {
    this->shootedInTurn = true;
    this->weapon = w_null;
}

void Worm::hurt(int damage) {
    if (this->health - damage < 0) {
        this->health = 0;
    } else {
        this->health -=damage;
    }
    this->hurtInTurn = true;
}

bool Worm::isWalking(void) {
    b2Vec2 velocity = this->body->GetLinearVelocity();
    return (velocity.y || velocity.x) && isGrounded();
}

bool Worm::isMoving(void) {
    b2Vec2 velocity = this->body->GetLinearVelocity();
    return velocity.y || velocity.x;
    //return this->wormPhysic.haveHorizontalSpeed() || this->wormPhysic.haveVerticalSpeed();
}

bool Worm::isFalling(void) {
    b2Vec2 velocity = this->body->GetLinearVelocity();
    return !isGrounded() && velocity.y;// && !jumping;
}

bool Worm::isGrounded(void) {
    return numFootContacts > 0;
}

bool Worm::isDead(void) {
    return this->health == 0;
}

void Worm::setAngle(float angle) {
    this->angle = angle;
}

void Worm::setFalling(bool falling) {
    this->falling = falling;
}

void Worm::update() {
    if (!this->isGrounded()) {
        if (this->falled && (getPosY() < this->fallenDistance)) {
            this->fallenDistance = getPosY();
        } else if (!this->falled){
            this->fallenDistance = getPosY();
            this->falled = true;
        }
    } else if (isGrounded() && (falled)) {
        this->fallenDistance = getPosY() - this->fallenDistance; 
        if (this->fallenDistance > gConfiguration.WORM_MAX_FALL_DISTANCE) {
            hurt(this->fallenDistance);
        }
        this->falled = false;
        this->fallenDistance = 0;
    }

    if (!this->body->GetLinearVelocity().x && !this->body->GetLinearVelocity().y) {
        this->affectedByExplosion = false;
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

    // Primer cuad rante
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

    

    if (getPosY() > gConfiguration.WORLD_Y_LIMIT) {
        this->kill();
    }

    if (normalX < 0 && normalY < 0 && !mirrored) {
        this->inclination = DOWN;
    } else if (normalX > 0 && normalY  < 0 && !mirrored) {
        this->inclination = UP;
    } else if (normalX < 0 && normalY  < 0 && mirrored) {
        this->inclination = UP;
    } else if (normalX > 0 && normalY  < 0 && mirrored) {
        this->inclination = DOWN;
    } else this->inclination = NONE;
}

bool Worm::isAffectedByExplosion() {
    return this->affectedByExplosion;
}

void Worm::setAffectedByExplosion(){
    this->affectedByExplosion = true;
}

void Worm::kill() {
    this->health = 0;
    this->hurtInTurn = true;
}

void Worm::refreshByNewTurn(void) {
    this->hurtInTurn = false;
    this->shootedInTurn = false;
}

bool Worm::gotHurtInTurn(void) {
    return this->hurtInTurn;
}

bool Worm::didShootInTurn(void) {
    return this->shootedInTurn;
}

void Worm::setPosition(float posX, float posY) {
    this->body->SetTransform(b2Vec2(posX, posY), this->body->GetAngle());
    this->body->SetAwake(true);
}

void Worm::setNormal(b2Vec2 normal) {
    std::cout << "NORMAL EN X " << normal.x << "NORMAL EN Y " << normal.y << std::endl;
    

    this->normalX = normal.x;
    this->normalY = normal.y;
}

worm_inclination_t Worm::getInclination() {
    return this->inclination;
}

int Worm::getDirectionAngle() {
    return this->direction_angle;
}

void Worm::equipWeapon(weapon_t weapon) {
    this->weapon = weapon;
}