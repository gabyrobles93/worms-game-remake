#include "dynamite.h"
#define DYNAMITE_FPC 3

View::Dynamite::Dynamite(SDL_Renderer * r) : sprite(DYNAMITE_FPC, ONLY_GOING) {
  this->texture.loadFromFile(gPath.PATH_DYNAMITE, r);
  this->sprite.setSpriteSheet(&this->texture);

	this->hasExploded = false;

	this->sound.setSound(gPath.PATH_SOUND_DYNAMITE);
}

View::Dynamite::~Dynamite() {

}

int View::Dynamite::getX(void) const {
	return this->x;
}

int View::Dynamite::getY(void) const {
	return this->y;
}

int View::Dynamite::getWidth(void) const {
  return this->texture.getWidth();
}

int View::Dynamite::getHeight(void) const {
  return this->texture.getHeight();
}

void View::Dynamite::setX(int x) {
	this->x = x - this->texture.getWidth() / 2;
}

void View::Dynamite::setY(int y) {
	this->y = y - this->texture.getWidth() / 2;
}

void View::Dynamite::render(SDL_Renderer * r, int camX, int camY) {
	if (!this->sprite.finished()) {
		this->sound.playSound();
		SDL_Rect clip = this->sprite.getNextClip();
		this->texture.render(r, this->x - camX, this->y - camY, &clip);
	} else {
		this->hasExploded = true;
		this->sound.stopSound();
		this->sound.setSound(gPath.PATH_SOUND_EXPLOSION_2);
		this->sound.playSound(0);
	}
}

bool View::Dynamite::exploded(void) {
	return this->hasExploded;
}