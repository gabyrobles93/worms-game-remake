#ifndef WIND_H
#define WIND_H

#include "Box2D.h"
#include "Configuration.h"
#include <stdlib.h>

class Wind {
private:
    int max_wind_force;
    int min_wind_force;
    int wind_force;
public:
    Wind();
    ~Wind();
    void updateWindForce();
    int getWindForce();
};

#endif