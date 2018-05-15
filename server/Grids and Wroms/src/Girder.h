#ifndef GIRDER_H
#define GIRDER_H

#include "Box2D/Box2D.h"

#define DENSITY 0.0f;
#define FRICTION 1.0f;

class Girder {
private: 
	b2Body* body;
public:
	Girder(b2World& world, float32 x, float32 y, float32 width, float32 height, float32 angle);
	//~Girder();
	b2Vec2 getPosition();
	float32 getAngle();
};

#endif