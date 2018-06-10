#include "bazooka.h"

#define BAZOOKA_FPC 3

View::Bazooka::Bazooka(SDL_Renderer * r, int ratioExplosion) :
  sprite(BAZOOKA_FPC, DEPENDENT_ON_GRADES),
	explosion(r, ratioExplosion, "Bazooka") {
  this->texture.loadFromFile(gPath.PATH_BAZOOKA, r);
  this->sprite.setSpriteSheet(&this->texture);

	this->exploded = false;
	this->finished = false;

	this->sound.setSound(gPath.PATH_SOUND_THROW_PROJECTIL);
  this->sound.playSound(0);
	this->ratioExplosion = ratioExplosion;

	this->playedAboutToExplode = false;
}

View::Bazooka::~Bazooka() {

}

void View::Bazooka::render(SDL_Renderer * r, int camX, int camY) {
  if (!this->exploded) {
		// Render Bazooka animation
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