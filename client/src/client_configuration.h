#ifndef __CLIENT_CONFIGURATION_H__
#define __CLIENT_CONFIGURATION_H__

#include <iostream>
#include <SDL2/SDL.h>
#include "types.h"
#include "sdl_timer.h"
#include "sound_effect.h"
#include "shoot_power.h"
#include "paths.h"

class ClientConfiguration {
  private:
    worm_data_cfg_t wormDataConfig;
    int weaponsCountdown;
    int sightAngle;
    int powerShoot;
    bool shooting;
    bool shooted;
    Timer shootingTimer;
    SoundEffect shootingSound;
    View::ShootPower shootPower;


  public:
    ClientConfiguration();
    ~ClientConfiguration();

    void handleEvent(SDL_Event &);

    int getWeaponsCountdown(void) const;
    bool hasShooted(void) const;
    int getPowerShoot(void);
    void render(SDL_Renderer *);
};

#endif