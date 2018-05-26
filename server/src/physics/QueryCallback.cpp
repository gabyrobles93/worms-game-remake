#include "QueryCallback.h"

bool QueryCallback::ReportFixture(b2Fixture* fixture) {
    foundBodies.push_back(fixture->GetBody());
    return true;
}