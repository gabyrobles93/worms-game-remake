#include "explosion.h"

View::Explosion::Explosion(SDL_Renderer * r, int ratio, std::string weapon) :
  sprite(EXPLOSION_FPC, ONLY_GOING) {
  this->texture.loadFromFile(gPath.PATH_EXPLOSION_EFFECT, r);
  this->width = ratio * 2;
  this->height = ratio * 2;
  this->x = 0;
  this->y = 0;

  this->sprite.setSpriteSheet(&this->texture);
  if (weapon == "Bazooka") {
    this->sound.setSound(gPath.PATH_SOUND_EXPLOSION_3); 
  } else if (weapon == "Grenade") {
    this->sound.setSound(gPath.PATH_SOUND_EXPLOSION_2);
  } else {
    this->sound.setSound(gPath.PATH_SOUND_EXPLOSION_1);
  }
  this->soundPlayed = false;
}

View::Explosion::~Explosion() {

}

int View::Explosion::getX(void) const {
	return this->x;
}

int View::Explosion::getY(void) const {
	return this->y;
}

int View::Explosion::getWidth(void) const {
  return this->width;
}

int View::Explosion::getHeight(void) const {
  return this->height;
}

void View::Explosion::setX(int x) {
	this->x = x - this->width / 2;
}

void View::Explosion::setY(int y) {
	this->y = y - this->height / 2;
}

void View::Explosion::render(SDL_Renderer * r, int camX, int camY) {
  if (!this->sprite.finished()) {
    if (!this->soundPlayed) {
      this->sound.playSound(0);
      this->soundPlayed = true;
    }
		SDL_Rect clip = this->sprite.getNextClip();
		this->texture.render(r, this->x - camX, this->y - camY, this->width, this->height, &clip);
	} 
}

bool View::Explosion::finishedExplosion(void) {
  return this->sprite.finished();
}