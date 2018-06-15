#include "client_configuration.h"

#define CHOP_ANGLE 3
#define MAX_SIGHT_ANGLE 90
#define MIN_SIGHT_ANGLE -90
#define MAX_TIME_SHOOTING 1500

#define VIEW_SHOOT_POWER_WIDTH 300
#define VIEW_SHOOT_POWER_HEIGHT 50

#define SCREEN_PADDING 10

#define MAX_WEAPONS 10
#define SCREEN_PERCENT_CLOCK 10
#define SCREEN_PERCENT_INVENTORY 50
#define SCREEN_PERCENT_SHOOT_POWER_HEIGHT 5
#define SCREEN_PERCENT_SHOOT_POWER_WIDTH 30

#define SCREEN_PERCENT_WIND_HEIGHT 5
#define SCREEN_PERCENT_WIND_WIDTH 30

#define SCREEN_PERCENT_TEAMS_HEALTH_HEIGHT 10
#define SCREEN_PERCENT_TEAMS_HEALTH_WIDTH 20

ClientConfiguration::ClientConfiguration(SDL_Renderer * r, int screenW, int screenH, const YAML::Node & staticMap) :
  shootPower(
    screenW / (100 / SCREEN_PERCENT_SHOOT_POWER_WIDTH), 
    screenH / (100 / SCREEN_PERCENT_SHOOT_POWER_HEIGHT), 
    MAX_TIME_SHOOTING
  ),
  clock( 
    screenH / (100 / SCREEN_PERCENT_CLOCK), 
    screenH / (100 / SCREEN_PERCENT_CLOCK)
  ),
  inventory(
    r,
    staticMap["init_inventory"]
  ),
  wind(
    r,
    screenW / (100 / SCREEN_PERCENT_WIND_WIDTH), 
    screenH / (100 / SCREEN_PERCENT_WIND_HEIGHT) 
  ),
  teamsHealth(
    r,
    screenW / (100 / SCREEN_PERCENT_TEAMS_HEALTH_WIDTH), 
    screenH / (100 / SCREEN_PERCENT_TEAMS_HEALTH_HEIGHT),
    staticMap["teams_amount"].as<int>(),
    staticMap["worms_health"].as<int>()
  ) {

  int clockX = SCREEN_PADDING + this->clock.getWidth() / 2;
  int clockY = screenH - SCREEN_PADDING - this->clock.getHeight() / 2;
  this->clock.setX(clockX);
  this->clock.setY(clockY);

  int shootX = screenW - SCREEN_PADDING - this->shootPower.getWidth() / 2;
  int shootY = screenH - SCREEN_PADDING - this->shootPower.getHeight() / 2 - this->wind.getHeight() - SCREEN_PADDING;
  this->shootPower.setX(shootX);
  this->shootPower.setY(shootY);

  int windX = screenW - SCREEN_PADDING - this->wind.getWidth() / 2;
  int windY = screenH - SCREEN_PADDING - this->wind.getHeight() / 2;
  this->wind.setX(windX);
  this->wind.setY(windY);

  int teamsHealthX = SCREEN_PADDING + this->clock.getWidth() + SCREEN_PADDING + this->teamsHealth.getWidth() / 2;
  int teamsHealthY = screenH - SCREEN_PADDING - this->teamsHealth.getHeight() / 2;
  this->teamsHealth.setX(teamsHealthX);
  this->teamsHealth.setY(teamsHealthY);

  this->inventory.setIconSide(screenH / (100 / SCREEN_PERCENT_INVENTORY) / MAX_WEAPONS);
  
  this->sightAngle = 0;
  this->weaponsCountdown = 5;
  this->wormDataConfig = ALL;
  this->shooting = false;
  this->shooted = false;
  this->powerShoot = -1;
  this->shootingSound.setSound(gPath.PATH_SOUND_THROW_POWER_UP);

  this->remoteControlX = 0;
  this->remoteControlY = 0;

  this->wormProtagonicId = 1;
}

ClientConfiguration::~ClientConfiguration() {

}

void ClientConfiguration::handleEvent(SDL_Event & e) {
  this->inventory.handleEvent(e);
  weapon_t weapon = this->inventory.getSelectedWeapon();

  if (e.type == SDL_MOUSEBUTTONDOWN) {
    if (e.button.button == SDL_BUTTON_LEFT) {
      if (weapon == w_air_strike || weapon == w_teleport) {
        this->shooted = true;
        SDL_GetMouseState(&this->remoteControlX, &this->remoteControlY);
      }
    }
  }

  if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_1) {
			this->weaponsCountdown = 1;
		}

		if (e.key.keysym.sym == SDLK_2) {
			this->weaponsCountdown = 2;
		}

		if (e.key.keysym.sym == SDLK_3) {
			this->weaponsCountdown = 3;
		}

		if (e.key.keysym.sym == SDLK_4) {
			this->weaponsCountdown = 4;
		}

		if (e.key.keysym.sym == SDLK_5) {
			this->weaponsCountdown = 5;
		}

    if (e.key.keysym.sym == SDLK_w) {
      if (this->sightAngle + CHOP_ANGLE > MAX_SIGHT_ANGLE) {
        this->sightAngle = MAX_SIGHT_ANGLE;
      } else {
        this->sightAngle += CHOP_ANGLE;
      }
    }

    if (e.key.keysym.sym == SDLK_s) {
      if (this->sightAngle - CHOP_ANGLE < MIN_SIGHT_ANGLE) {
        this->sightAngle = MIN_SIGHT_ANGLE;
      } else {
        this->sightAngle -= CHOP_ANGLE;
      }
	  }

    if (e.key.keysym.sym == SDLK_DELETE) {
      if (this->wormDataConfig == ALL) {
        this->wormDataConfig = ONLY_HEALTH;
        return;
      }

      if (this->wormDataConfig == ONLY_HEALTH) {
        this->wormDataConfig = NO_DATA;
        return;
      }

      if (this->wormDataConfig == NO_DATA) {
        this->wormDataConfig = ALL;
        return;
      }
    }

    if (e.key.keysym.sym == SDLK_h) {
      this->teamsHealth.toggleHide();
    }

    if (e.key.keysym.sym == SDLK_SPACE && weapon != w_air_strike && weapon != w_teleport) {
      if (!this->shootingTimer.isStarted()) {
        this->shootingSound.playSound(0);
        this->shootingTimer.start();
        this->shooting = true;
      }
    }
  }

  if (this->shootingTimer.isStarted()) {
    if (this->shootingTimer.getTicks() >= MAX_TIME_SHOOTING) {
      this->shootingSound.stopSound();
      this->powerShoot = MAX_TIME_SHOOTING;
      this->shootingTimer.stop();
      this->shooting = false;
      this->shooted = true;
    }
  }

  if (e.type == SDL_KEYUP) {
    if (e.key.keysym.sym == SDLK_SPACE && this->shooting) {
      this->shootingSound.stopSound();
      this->shooting = false;
      this->shooted = true;
      this->powerShoot = this->shootingTimer.getTicks();
      this->shootingTimer.stop();
    }
  }
}

int ClientConfiguration::getWeaponsCountdown(void) const {
  return this->weaponsCountdown;
}

bool ClientConfiguration::hasShooted(void) const {
  return this->shooted;
}

int ClientConfiguration::getPowerShoot(void) {
  int pshoot = this->powerShoot;
  this->shooted = false;
  this->powerShoot = -1;
  return pshoot;
}

void ClientConfiguration::render(SDL_Renderer * r) {
  if (this->shooting) {
    this->shootPower.render(r, this->shootingTimer.getTicks());
  }

  this->wind.render(r, 0, 0);

  this->inventory.render(r);
  this->clock.render(r, 0, 0);

  this->teamsHealth.render(r, 0, 0);
}

weapon_t ClientConfiguration::getSelectedWeapon(void) {
  return this->inventory.getSelectedWeapon();
}

void ClientConfiguration::update(const YAML::Node & gameStatus, const YAML::Node & inventory) {
  //std::cout << gameStatus << std::endl << std::endl;
  int newTime = gameStatus["turn_timeleft"].as<int>();
  int windForce = gameStatus["wind_force"].as<int>();
  this->wormProtagonicId = gameStatus["protagonic_worm"].as<int>();
  const YAML::Node & teamsHealthNode = gameStatus["teams_health"];

  if (newTime) {
    this->clock.toggleHide(false);
  } else {
    this->clock.toggleHide(true);
  }

  this->clock.setTime(newTime);
  this->wind.setWindPower(windForce);
  this->teamsHealth.update(teamsHealthNode);
}

int ClientConfiguration::getSightAngle(void) {
  return this->sightAngle;
}

worm_data_cfg_t ClientConfiguration::getWormDataConfiguration(void) {
  return this->wormDataConfig;
}

int ClientConfiguration::getRemoteControlX(void) {
  this->shooted = false;
  return this->remoteControlX;
}

int ClientConfiguration::getRemoteControlY(void) {
  this->shooted = false;
  return this->remoteControlY;
}

size_t ClientConfiguration::getWormProtagonicId(void) {
  return this->wormProtagonicId;
}

