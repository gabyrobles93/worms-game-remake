#include "Configuration.h"

Configuration::Configuration() {
    //CONVERSION
    this->SCALING_FACTOR = 0.0416;
    this->DEGTORAD = 0.0174533;

    //WORLD
    this->WORLD_TIME_STEP = 1.0f/60.0f;
    this->WORLD_VELOCITY_ITERATIONS = 6;
    this->WORLD_POSITION_ITERATIONS = 2;

    //WORM
    this->WORM_SPEED = 1;

    //BAT
    this->BAT_DAMAGE = 10;

    //DYNAMITE
    this->DYNAMITE_BLAST_RADIUS = 10;
    this->DYNAMITE_BLAST_POWER =50;
    
    //GREEN GRENADE
    this->GREEN_GRENADE_BLAST_RADIUS = 2;
    this->GREEN_GRENADE_BLAST_POWER = 30;
}