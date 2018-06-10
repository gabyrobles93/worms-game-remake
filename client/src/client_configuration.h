#ifndef __CLIENT_CONFIGURATION_H__
#define __CLIENT_CONFIGURATION_H__

#include <iostream>
#include <SDL2/SDL.h>
#include "clock.h"
#include "inventory_weapons.h"
#include "types.h"
#include "sdl_timer.h"
#include "sound_effect.h"
#include "shoot_power.h"
#include "paths.h"
#include "yaml.h"

class ClientConfiguration {
  private:
    worm_data_cfg_t wormDataConfig;
    int weaponsCountdown;
    int sightAngle;
    int powerShoot;
    int remoteControlX;
    int remoteControlY;
    bool shooting;
    bool shooted;
    Timer shootingTimer;
    SoundEffect shootingSound;
    View::ShootPower shootPower;
    View::Clock clock;
    View::WeaponsInventory inventory;

  public:
    ClientConfiguration(SDL_Renderer *, int, int, const YAML::Node &);
    ~ClientConfiguration();

    void handleEvent(SDL_Event &);

    int getWeaponsCountdown(void) const;
    bool hasShooted(void) const;
    int getPowerShoot(void);
    void render(SDL_Renderer *);

    // Retorna el weapon_t seleccionado
    weapon_t getSelectedWeapon(void);

    // Retorna el worm_data_cfg_t configurado
    worm_data_cfg_t getWormDataConfiguration(void);

    // Retorna el sight_angle configurado
    int getSightAngle(void);

    // Retorna la posicion X/Y del teledirigido
    int getRemoteControlX(void);
    int getRemoteControlY(void);

    // Updatea la configuracion que muestra el cliente
    void update(const YAML::Node &, const YAML::Node &);
};

#endif