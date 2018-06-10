#include "air_strike.h"

#define AIR_STRIKE 3

View::AirStrike::AirStrike(SDL_Renderer * r, int ratioExplosion) :
  sprite(AIR_STRIKE, DEPENDENT_ON_GRADES),
	explosion(r, ratioExplosion, "Bazooka") {
  this->texture.loadFromFile(gPath.PATH_AIR_STRIKE, r);
  this->sprite.setSpriteSheet(&this->texture);

	this->exploded = false;
	this->finished = false;

	this->sound.setSound(gPath.PATH_SOUND_AIR_STRIKE);
  this->sound.playSound(0);
	this->ratioExplosion = ratioExplosion;

	this->playedAboutToExplode = false;
}

View::AirStrike::~AirStrike() {

}

void View::AirStrike::render(SDL_Renderer * r, int camX, int camY) {
  if (!this->exploded) {
		// Render AirStrike animation
		SDL_Rect clip = this->sprite.getNextClip(this->angleDirection);
		this->texture.render(r, this->x - camX, this->y - camY, &clip);
	} else {
		if (!this->explosion.finishedExplosion()) {
			this->explosion.setX(this->x + this->getWidth() / 2);
			this->explosion.setY(this->y + this->getHeight() / 2);
			this->explosion.render(r, camX, camY);
		} else {
			this->finished = true;
		}
	}
}