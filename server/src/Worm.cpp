#include "Worm.h"

Worm::Worm(b2World &world, float32 x, float32 y) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x,y);
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(WORM_WIDTH/2, WORM_HEIGHT/2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = WORM_DENSITY;
	fixtureDef.friction = WORM_FRICTION;

	body->CreateFixture(&fixtureDef);

	this->body = body;
}

b2Vec2 Worm::getPosition() {
	return this->body->GetPosition();
}

float32 Worm::getAngle() {
	return this->body->GetAngle();
}

void Worm::moveRight() {
	b2Vec2 velocity = this->body->GetLinearVelocity();
	velocity.x = MOVE_VELOCITY;
	this->body->SetLinearVelocity(velocity);
}

void Worm::moveLeft() {
	b2Vec2 velocity = this->body->GetLinearVelocity();
	velocity.x = -MOVE_VELOCITY;
	this->body->SetLinearVelocity(velocity);
}

void Worm::stopMoving() {
	b2Vec2 velocity = this->body->GetLinearVelocity();
	velocity.x = 0;
	this->body->SetLinearVelocity(velocity);
}

void Worm::jumpBack() {

}

void Worm::jumpFoward() {

	//float impulseX = this->body->GetMass() * 2.17;
	//float impulseY = this->body->GetMass() * 1.2;
	//this->body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), this->body->GetWorldCenter(), true);
}
