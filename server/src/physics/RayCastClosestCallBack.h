#ifndef RAYCAST_CLOSEST_CALL_BACK_H
#define RAYCAST_CLOSEST_CALL_BACK_H

#include "Box2D.h"

class RayCastClosestCallBack : public b2RayCastCallback {
public:
    RayCastClosestCallBack ();
    b2Body* body;
    b2Vec2 point;

    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
};

#endif