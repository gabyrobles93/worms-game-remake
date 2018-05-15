#ifndef WORM_H
#define WORM_H

#include "Box2D/Box2D.h"
#define MOVE_VELOCITY 2.0f
#define WORM_HEIGHT 0.8f
#define WORM_WIDTH 0.8f
#define WORM_DENSITY 1.0f
#define WORM_FRICTION 0.3f

class Worm {
private:
	//b2World& world;
	b2Body* body;
public:
	Worm(b2World& world, float32 x, float32 y);
	b2Vec2 getPosition();
	float32 getAngle();
	void stopMoving();
	void moveRight();
	void moveLeft();
	void jumpBack();
	void jumpFoward();
};


#endif