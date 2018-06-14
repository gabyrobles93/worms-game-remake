#include "Configuration.h"

Configuration::Configuration() {
    //TURN
    this->TURN_DURATION = 50;
    //CONVERSION
    this->SCALING_FACTOR = 0.0416;
    this->DEGTORAD = 0.0174533;
    this->RADTODEG = 57.2958;

    //WORLD
    this->WORLD_TIME_STEP = 1.0f/60.0f;
    this->WORLD_VELOCITY_ITERATIONS = 6;
    this->WORLD_POSITION_ITERATIONS = 2;
    this->WORLD_Y_LIMIT = 58.24f;

    //WORM
    this->WORM_SPEED = 2;
    this->WORM_JUMP_IMPULSE = 4;
    this->WORM_MAX_FALL_DISTANCE = 4;

    //BAZOOKA
    this->BAZOOKA_BLAST_RADIUS = 2;
    this->BAZOOKA_BLAST_POWER = 50;

    //MORTAR
    this->MORTAR_BLAST_RADIUS = 2;
    this->MORTAR_BLAST_POWER = 50;
    this->MORTAR_FRAGMENT_QUANTITY = 6;
    this->MORTAR_FRAGMENT_BLAST_RADIUS = 2;
    this->MORTAR_FRAGMENT_BLAST_POWER = 10;

    //WIND
    this->MAX_WIND_FORCE = 6;
    this->MIN_WIND_FORCE = -6;
    
    //GRENADE
    this->GRENADE_RESTITUTION = 0.6;

    //RED GRENADE
    this->RED_GRENADE_BLAST_RADIUS = 2;
    this->RED_GRENADE_BLAST_POWER = 30;
    this->RED_GRENADE_FRAGMENT_QUANTITY = 50;
    this->RED_GRENADE_FRAGMENT_BLAST_RADIUS = 2;
    this->RED_GRENADE_FRAGMENT_BLAST_POWER = 10;

    //BANANA
    this->BANANA_BLAST_RADIUS = 4;
    this->BANANA_BLAST_POWER = 70;

    //HOLY GRENADE
    this->HOLY_GRENADE_BLAST_RADIUS = 8;
    this->HOLY_GRENADE_BLAST_POWER = 110;

    //AIRSTRIKE
    this->AIR_STRIKE_BLAST_RADIUS = 2;
    this->AIR_STRIKE_BLAST_POWER = 40;
    this->AIR_STRIKE_MISSIL_QUANTITY = 6;

    //BAT
    this->BAT_DAMAGE = 10;
    this->BAT_LENGTH = 1;
    this->BAT_IMPULSE = 10;

    //DYNAMITE
    this->DYNAMITE_BLAST_RADIUS = 4;
    this->DYNAMITE_BLAST_POWER =50;
    
    //GREEN GRENADE
    this->GREEN_GRENADE_BLAST_RADIUS = 2;
    this->GREEN_GRENADE_BLAST_POWER = 30;
}