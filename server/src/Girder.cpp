#include "Girder.h"

Girder::Girder(b2World& world, float32 x, float32 y, float32 width, float32 height, float32 angle) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(x,y);
	bodyDef.angle = angle;
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox(width/2, height/2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = DENSITY;
	fixtureDef.friction = FRICTION;
	body->CreateFixture(&fixtureDef);

	this->body = body;
}

b2Vec2 Girder::getPosition() {
	return this->body->GetPosition();
}

float32 Girder::getAngle() {
	return this->body->GetAngle();
}