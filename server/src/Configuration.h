#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class Configuration {
public:
    Configuration();
    //CONVERSIONS
    float DEGTORAD;
    float SCALING_FACTOR;

    //WORLD
    float WORLD_TIME_STEP;
    float WORLD_VELOCITY_ITERATIONS;
    float WORLD_POSITION_ITERATIONS;
    
    //WORM
    float WORM_SPEED;

    //BAT
    int BAT_DAMAGE;

    //DYNAMITE
    int DYNAMITE_BLAST_RADIUS;
    int DYNAMITE_BLAST_POWER;
    
    //GREEN GRENADE
    int GREEN_GRENADE_BLAST_RADIUS;
    int GREEN_GRENADE_BLAST_POWER;
};

extern Configuration gConfiguration;

#endif