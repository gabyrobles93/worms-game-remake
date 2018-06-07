#include "green_grenade.h"

#define GREEN_GRENADE_FPC 3

View::GreenGrenade::GreenGrenade(SDL_Renderer * r, int countdown, int ratioExplosion) : 
	sprite(GREEN_GRENADE_FPC, INFINITE_GOING_AND_BACK),
	explosion(r, ratioExplosion, "Grenade"),
	countdownText(COUNTDOWN_TEXT_SIZE) {
  this->texture.loadFromFile(gPath.PATH_GREEN_GRENADE, r);
  this->sprite.setSpriteSheet(&this->texture);

	this->exploded = false;
	this->finished = false;
	this->playedAboutToExplode = false;

	this->sound.setSound(gPath.PATH_SOUND_THROW_PROJECTIL);
  this->sound.playSound(0);
	this->countdown = countdown;
	this->ratioExplosion = ratioExplosion;
}

View::GreenGrenade::~GreenGrenade() {

}

void View::GreenGrenade::render(SDL_Renderer * r, int camX, int camY) {
	if (!this->exploded) {
		// Render GreenGrenade animation
		SDL_Rect clip = this->sprite.getNextClip();
		this->texture.render(r, this->x - camX, this->y - camY, &clip);

		// Render countdown text
		this->countdownText.setText(r, std::to_string(this->countdown));
		this->countdownText.setX(this->x + this->texture.getWidth() - this->countdownText.getWidth());
		this->countdownText.setY(this->y + this->countdownText.getHeight());
		this->countdownText.render(r, camX, camY);
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