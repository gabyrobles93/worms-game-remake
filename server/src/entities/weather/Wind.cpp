#include "Wind.h"
#include <iostream>

Wind::Wind() {
    this->max_wind_force = gConfiguration.MAX_WIND_FORCE;
    this->min_wind_force = gConfiguration.MIN_WIND_FORCE;
    this->wind_force = (rand()%(max_wind_force - min_wind_force + 1 )) + min_wind_force;
}

Wind::~Wind() {

}

int Wind::getWindForce() {
    return this->wind_force;
}

void Wind::updateWindForce() {
    this->wind_force = (rand()%(max_wind_force - min_wind_force + 1 )) + min_wind_force;
}