#ifndef QUERY_CALLBACK_H
#define QUERY_CALLBACK_H

#include "Box2D.h"

class QueryCallback : public b2QueryCallback {
public:
    std::vector<b2Body*> foundBodies;
    bool ReportFixture(b2Fixture* fixture);
};

#endif