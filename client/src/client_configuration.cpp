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

ClientConfiguration::ClientConfiguration(SDL_Renderer * r, int screenW, int screenH, const YAML::Node & inv) :
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
    inv
  ) {

  int clockX = SCREEN_PADDING;
  int clockY = screenH - SCREEN_PADDING - this->clock.getHeight();
  this->clock.setX(clockX);
  this->clock.setY(clockY);

  int shootX = screenW - SCREEN_PADDING - this->shootPower.getWidth() / 2;
  int shootY = screenH - SCREEN_PADDING - this->shootPower.getHeight() / 2;
  this->shootPower.setX(shootX);
  this->shootPower.setY(shootY);

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
        this->wormDataConfig = NONE;
        return;
      }

      if (this->wormDataConfig == NONE) {
        this->wormDataConfig = ALL;
        return;
      }
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

  this->inventory.render(r);
  this->clock.render(r, 0, 0);
}

weapon_t ClientConfiguration::getSelectedWeapon(void) {
  return this->inventory.getSelectedWeapon();
}

void ClientConfiguration::update(const YAML::Node & gameStatus, const YAML::Node & inventory) {
  int newTime = gameStatus["turn_timeleft"].as<int>();
  if (newTime) {
    this->clock.toggleHide(false);
  } else {
    this->clock.toggleHide(true);
  }

  this->clock.setTime(newTime);
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

