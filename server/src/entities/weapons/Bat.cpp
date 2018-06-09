#include "Bat.h"
#include "types.h"

Bat::Bat(b2World& world, float posX, float posY, float angle) :
Weapon(w_bat),
world(world) {
    b2BodyDef batDef;
    batDef.type = b2_dynamicBody;
    batDef.fixedRotation = true;
    batDef.angle = angle;
    batDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&batDef);
    body->SetUserData(this);

    b2PolygonShape batShape;
    batShape.SetAsBox(BAT_WIDTH/2, BAT_HEIGTH/2);

    b2FixtureDef batFixture;
    batFixture.shape = &batShape;
    batFixture.density = 1;
    batFixture.friction = 1;
    batFixture.filter.categoryBits = BAT_PHYSIC;
    batFixture.filter.maskBits = WORM_PHYSIC;
    body->CreateFixture(&batFixture);
    this->body = body;

}

Bat::~Bat() {
    this->world.DestroyBody(this->body);
}

void Bat::atack(Worm* worm) {
    worm->hurt(gConfiguration.BAT_DAMAGE);
}