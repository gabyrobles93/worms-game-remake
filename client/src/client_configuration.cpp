#include "client_configuration.h"

#define CHOP_ANGLE 3
#define MAX_SIGHT_ANGLE 90
#define MIN_SIGHT_ANGLE -90
#define MAX_TIME_SHOOTING 1500

#define VIEW_SHOOT_POWER_WIDTH 300
#define VIEW_SHOOT_POWER_HEIGHT 50

ClientConfiguration::ClientConfiguration() :
  shootPower(VIEW_SHOOT_POWER_WIDTH, VIEW_SHOOT_POWER_HEIGHT, MAX_TIME_SHOOTING) {
  this->sightAngle = 0;
  this->weaponsCountdown = 5;
  this->wormDataConfig = ALL;
  this->shooting = false;
  this->shooted = false;
  this->powerShoot = -1;
  this->shootingSound.setSound(gPath.PATH_SOUND_THROW_POWER_UP);
}

ClientConfiguration::~ClientConfiguration() {

}

void ClientConfiguration::handleEvent(SDL_Event & e) {
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

    if (e.key.keysym.sym == SDLK_SPACE) {
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
}