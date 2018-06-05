#include "dynamite.h"
#define DYNAMITE_FPC 3
#define COUNTDOWN_TEXT_SIZE 18

View::Dynamite::Dynamite(SDL_Renderer * r, int countdown, int ratioExplosion) : 
	sprite(DYNAMITE_FPC, INFINITE_GOING_AND_BACK),
	explosion(r, ratioExplosion, "Dynamite"),
	countdownText(COUNTDOWN_TEXT_SIZE) {
  this->texture.loadFromFile(gPath.PATH_DYNAMITE, r);
  this->sprite.setSpriteSheet(&this->texture);

	this->exploded = false;
	this->finished = false;

	this->sound.setSound(gPath.PATH_SOUND_DYNAMITE);
	this->countdown = countdown;
	this->ratioExplosion = ratioExplosion;
}

View::Dynamite::~Dynamite() {

}

void View::Dynamite::render(SDL_Renderer * r, int camX, int camY) {
	if (!this->exploded) {
		this->sound.playSound();

		// Render dynamite animation
		SDL_Rect clip = this->sprite.getNextClip();
		this->texture.render(r, this->x - camX, this->y - camY, &clip);

		// Render countdown text
		this->countdownText.setText(r, std::to_string(this->countdown));
		this->countdownText.setX(this->x + this->texture.getWidth() - this->countdownText.getWidth());
		this->countdownText.setY(this->y + this->countdownText.getHeight());
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