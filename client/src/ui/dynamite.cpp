#include "dynamite.h"
#define DYNAMITE_FPC 3

View::Dynamite::Dynamite(SDL_Renderer * r, int countdown, int ratioExplosion) : 
	sprite(DYNAMITE_FPC, INFINITE_GOING_AND_BACK) {
  this->texture.loadFromFile(gPath.PATH_DYNAMITE, r);
  this->sprite.setSpriteSheet(&this->texture);

	this->exploded = false;
	this->finished = false;

	this->sound.setSound(gPath.PATH_SOUND_DYNAMITE);
	this->countdown = countdown;
	this->ratioExplotion = ratioExplosion;
}

View::Dynamite::~Dynamite() {

}

void View::Dynamite::render(SDL_Renderer * r, int camX, int camY) {
	if (!this->exploded) {
		this->sound.playSound();
		SDL_Rect clip = this->sprite.getNextClip();
		this->texture.render(r, this->x - camX, this->y - camY, &clip);
	} else {
		this->sound.stopSound();
		this->sound.setSound(gPath.PATH_SOUND_EXPLOSION_2);
		this->sound.playSound(0);
	}
}