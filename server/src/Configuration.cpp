#include <iostream>
#include "Configuration.h"

Configuration::Configuration() {
    //TURN
    this->TURN_DURATION = 50; //
    //CONVERSION
    this->SCALING_FACTOR = 0.0416; //
    this->DEGTORAD = 0.0174533; //
    this->RADTODEG = 57.2958; //

    //WORLD
    this->WORLD_TIME_STEP = 1.0f/60.0f; //
    this->WORLD_VELOCITY_ITERATIONS = 6; //
    this->WORLD_POSITION_ITERATIONS = 2; //
    this->WORLD_Y_LIMIT = 58.24f;

    //WORM
    this->WORM_SPEED = 2;   //
    this->WORM_JUMP_IMPULSE = 4; //
    this->WORM_MAX_FALL_DISTANCE = 4; //

    //BAZOOKA
    this->BAZOOKA_BLAST_RADIUS = 2; //
    this->BAZOOKA_BLAST_POWER = 50; //

    //MORTAR
    this->MORTAR_BLAST_RADIUS = 2; //
    this->MORTAR_BLAST_POWER = 50; //
    this->MORTAR_FRAGMENT_QUANTITY = 6; //
    this->MORTAR_FRAGMENT_BLAST_RADIUS = 2; //
    this->MORTAR_FRAGMENT_BLAST_POWER = 10; //

    //WIND
    this->MAX_WIND_FORCE = 6; //
    this->MIN_WIND_FORCE = -6; //
    
    //GRENADE
    this->GRENADE_RESTITUTION = 0.6; //

    //RED GRENADE
    this->RED_GRENADE_BLAST_RADIUS = 2; //
    this->RED_GRENADE_BLAST_POWER = 30; //
    this->RED_GRENADE_FRAGMENT_QUANTITY = 50; //
    this->RED_GRENADE_FRAGMENT_BLAST_RADIUS = 2; //
    this->RED_GRENADE_FRAGMENT_BLAST_POWER = 10; //

    //BANANA
    this->BANANA_BLAST_RADIUS = 4; //
    this->BANANA_BLAST_POWER = 70; //

    //HOLY GRENADE
    this->HOLY_GRENADE_BLAST_RADIUS = 8; //
    this->HOLY_GRENADE_BLAST_POWER = 110; //

    //AIRSTRIKE
    this->AIR_STRIKE_BLAST_RADIUS = 2; //
    this->AIR_STRIKE_BLAST_POWER = 40; //
    this->AIR_STRIKE_MISSIL_QUANTITY = 6; //

    //BAT
    this->BAT_DAMAGE = 10; //
    this->BAT_LENGTH = 1; //
    this->BAT_IMPULSE = 10; //

    //DYNAMITE
    this->DYNAMITE_BLAST_RADIUS = 4; //
    this->DYNAMITE_BLAST_POWER =50; //
    
    //GREEN GRENADE
    this->GREEN_GRENADE_BLAST_RADIUS = 2; //
    this->GREEN_GRENADE_BLAST_POWER = 30; //
}

void Configuration::loadConfigFile(YAML::Node & configNode) {
    size_t counter = 0;

    if (configNode["match"]["turn_duration"]) {
        this->TURN_DURATION = configNode["match"]["turn_duration"].as<float>(); //
        counter++;
    }

    if (configNode["world_physics"]["scaling_factor_pixels_meters"]) {
        this->SCALING_FACTOR = configNode["world_physics"]["scaling_factor_pixels_meters"].as<float>(); //
        counter++;
    }
   
    if (configNode["world_physics"]["scaling_degree_radian"]) {
        this->DEGTORAD = configNode["world_physics"]["scaling_degree_radian"].as<float>(); //
        counter++;
    }
    
    if (configNode["world_physics"]["scaling_radian_degree"]) {
        this->RADTODEG = configNode["world_physics"]["scaling_radian_degree"].as<float>(); //
        counter++;
    }
     
    if (configNode["world_physics"]["world_time_step"]) {
        this->WORLD_TIME_STEP = configNode["world_physics"]["world_time_step"].as<float>(); //
        counter++;
    }

    if (configNode["world_physics"]["world_velocity_iterations"]) {
        this->WORLD_VELOCITY_ITERATIONS = configNode["world_physics"]["world_velocity_iterations"].as<float>(); //
        counter++;
    }

    if (configNode["world_physics"]["world_position_iterations"]) {
        this->WORLD_POSITION_ITERATIONS = configNode["world_physics"]["world_position_iterations"].as<float>(); //
        counter++;
    }

    if (configNode["world_physics"]["world_y_limit"]) {
        this->WORLD_Y_LIMIT = configNode["world_physics"]["world_y_limit"].as<float>(); //
        counter++;
    }

    if (configNode["world_physics"]["max_wind_force"]) {
        this->MAX_WIND_FORCE = configNode["world_physics"]["max_wind_force"].as<int>(); //
        counter++;
    }

    if (configNode["world_physics"]["min_wind_force"]) {
        this->MIN_WIND_FORCE = configNode["world_physics"]["min_wind_force"].as<int>(); //
        counter++;
    }

    if (configNode["worms"]["worms_speed"]) {
        this->WORM_SPEED = configNode["worms"]["worms_speed"].as<float>(); //
        counter++;
    }

    if (configNode["worms"]["worm_jump_impulse"]) {
        this->WORM_JUMP_IMPULSE = configNode["worms"]["worm_jump_impulse"].as<float>(); //
        counter++;
    }

    if (configNode["worms"]["worm_max_fall_distance"]) {
        this->WORM_MAX_FALL_DISTANCE = configNode["worms"]["worm_max_fall_distance"].as<int>(); //
        counter++;
    }

    if (configNode["weapons"]["physics"]["grenade_restitution"]) {
        this->GRENADE_RESTITUTION = configNode["weapons"]["physics"]["grenade_restitution"].as<float>(); //
        counter++;
    }

    if (configNode["weapons"]["bazooka"]) {
        this->BAZOOKA_BLAST_RADIUS = configNode["weapons"]["bazooka"]["radious"].as<int>(); //
        this->BAZOOKA_BLAST_POWER = configNode["weapons"]["bazooka"]["damage"].as<int>(); //
        counter += 2;
    }
    
    if (configNode["weapons"]["mortar"]) {
        this->MORTAR_BLAST_RADIUS = configNode["weapons"]["mortar"]["radious"].as<int>(); //
        this->MORTAR_BLAST_POWER = configNode["weapons"]["mortar"]["damage"].as<int>(); //
        this->MORTAR_FRAGMENT_QUANTITY = configNode["weapons"]["mortar"]["fragments_qty"].as<int>(); //
        this->MORTAR_FRAGMENT_BLAST_RADIUS = configNode["weapons"]["mortar"]["fragments_radious"].as<int>(); //
        this->MORTAR_FRAGMENT_BLAST_POWER = configNode["weapons"]["mortar"]["fragments_damage"].as<int>(); //
        counter += 5;
    }

    if (configNode["weapons"]["red_grenade"]) {
        this->RED_GRENADE_BLAST_RADIUS = configNode["weapons"]["red_grenade"]["radious"].as<int>(); //
        this->RED_GRENADE_BLAST_POWER = configNode["weapons"]["red_grenade"]["damage"].as<int>(); //
        this->RED_GRENADE_FRAGMENT_QUANTITY = configNode["weapons"]["red_grenade"]["fragments_qty"].as<int>(); //
        this->RED_GRENADE_FRAGMENT_BLAST_RADIUS = configNode["weapons"]["red_grenade"]["fragments_radious"].as<int>(); //
        this->RED_GRENADE_FRAGMENT_BLAST_POWER = configNode["weapons"]["red_grenade"]["fragments_damage"].as<int>(); //
        counter += 5;
    }

    if (configNode["weapons"]["banana"]) {
        this->BANANA_BLAST_RADIUS = configNode["weapons"]["banana"]["radious"].as<int>(); //
        this->BANANA_BLAST_POWER = configNode["weapons"]["banana"]["damage"].as<int>(); //
        counter += 2;
    }

    if (configNode["weapons"]["holy_grenade"]) {
        this->HOLY_GRENADE_BLAST_RADIUS = configNode["weapons"]["holy_grenade"]["radious"].as<int>(); //
        this->HOLY_GRENADE_BLAST_POWER = configNode["weapons"]["holy_grenade"]["damage"].as<int>(); //
        counter += 2;
    }

    if (configNode["weapons"]["air_strike"]) {
        this->AIR_STRIKE_BLAST_RADIUS = configNode["weapons"]["air_strike"]["radious"].as<int>(); //
        this->AIR_STRIKE_BLAST_POWER = configNode["weapons"]["air_strike"]["damage"].as<int>(); //
        this->AIR_STRIKE_MISSIL_QUANTITY = configNode["weapons"]["air_strike"]["qty"].as<int>(); //
        counter += 3;
    }

    if (configNode["weapons"]["bat"]) {
        this->BAT_DAMAGE = configNode["weapons"]["bat"]["damage"].as<int>(); //
        this->BAT_LENGTH = configNode["weapons"]["bat"]["length"].as<int>(); //
        this->BAT_IMPULSE = configNode["weapons"]["bat"]["impulse"].as<int>(); //
        counter += 3;
    }

    if (configNode["weapons"]["dynamite"]) {
        this->DYNAMITE_BLAST_RADIUS = configNode["weapons"]["dynamite"]["radious"].as<int>(); //
        this->DYNAMITE_BLAST_POWER = configNode["weapons"]["dynamite"]["damage"].as<int>(); //
        counter += 2;
    }

    if (configNode["weapons"]["green_grenade"]) {
        this->GREEN_GRENADE_BLAST_RADIUS = configNode["weapons"]["green_grenade"]["radious"].as<int>(); //
        this->GREEN_GRENADE_BLAST_POWER = configNode["weapons"]["green_grenade"]["damage"].as<int>(); //
        counter += 2;
    }
}
