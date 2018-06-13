#include "dynamite.h"
#define DYNAMITE_FPC 3

View::Dynamite::Dynamite(SDL_Renderer * r, int countdown, int ratioExplosion) : 
	sprite(DYNAMITE_FPC, INFINITE_GOING_AND_BACK),
	explosion(r, ratioExplosion, "Dynamite"),
	countdownText(COUNTDOWN_TEXT_SIZE) {
  this->texture.loadFromFile(gPath.PATH_DYNAMITE, r);
  this->sprite.setSpriteSheet(&this->texture);

	this->exploded = false;
	this->finished = false;

	const char * laughs[] = {
		gPath.PATH_SOUND_LAUGH.c_str(),
		gPath.PATH_SOUND_FATALITY.c_str()
	};

	this->laugh.setSound(laughs[rand() % 2]);
	this->laugh.playSound(0);

	this->sound.setSound(gPath.PATH_SOUND_DYNAMITE);
	this->sound.playSound();
	this->countdown = countdown;
	this->ratioExplosion = ratioExplosion;
}

View::Dynamite::~Dynamite() {

}

void View::Dynamite::render(SDL_Renderer * r, int camX, int camY) {
	if (!this->exploded) {
		// Render dynamite animation
		SDL_Rect clip = this->sprite.getNextClip();
		this->texture.render(r, this->x - camX, this->y - camY, &clip);

		// Render countdown text
		this->countdownText.setText(r, std::to_string(this->countdown));
		this->countdownText.setX(this->x + this->texture.getWidth() +  this->countdownText.getWidth() / 2);
		this->countdownText.setY(this->y - this->countdownText.getHeight() / 2);
		this->countdownText.render(r, camX, camY);
	} else {
		this->sound.stopSound();
		if (!this->explosion.finishedExplosion()) {
			this->explosion.setX(this->x + this->getWidth() / 2);
			this->explosion.setY(this->y + this->getHeight() / 2);
			this->explosion.render(r, camX, camY);
		} else {
			this->finished = true;
		}
	}
}