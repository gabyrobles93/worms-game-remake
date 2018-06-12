#include "RayCastClosestCallBack.h"

RayCastClosestCallBack::RayCastClosestCallBack() {
    this->body = NULL;
}

float32 RayCastClosestCallBack::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
    body = fixture->GetBody();
    this->point = point;
    return fraction;
}
