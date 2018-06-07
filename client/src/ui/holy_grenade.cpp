#include "holy_grenade.h"

#define HOLY_GRENADE_FPC 3
#define COUNTDOWN_HOLY_SOUND 2

View::HolyGrenade::HolyGrenade(SDL_Renderer * r, int countdown, int ratioExplosion) : 
	sprite(HOLY_GRENADE_FPC, INFINITE_GOING_AND_BACK),
	explosion(r, ratioExplosion, "Holy Grenade"),
	countdownText(COUNTDOWN_TEXT_SIZE) {
  this->texture.loadFromFile(gPath.PATH_HOLY_GRENADE, r);
  this->sprite.setSpriteSheet(&this->texture);

	this->exploded = false;
	this->finished = false;

	this->sound.setSound(gPath.PATH_SOUND_THROW_PROJECTIL);
  this->sound.playSound(0);
	this->countdown = countdown;
	this->ratioExplosion = ratioExplosion;

  this->holySound.setSound(gPath.PATH_SOUND_HOLY);
  this->holySoundPlayed = false;
	this->playedAboutToExplode = false;
}

View::HolyGrenade::~HolyGrenade() {

}

void View::HolyGrenade::render(SDL_Renderer * r, int camX, int camY) {
	if (!this->exploded) {
		// Render HolyGrenade animation
		SDL_Rect clip = this->sprite.getNextClip();
		this->texture.render(r, this->x - camX, this->y - camY, &clip);

    if (!this->holySoundPlayed && this->countdown <= COUNTDOWN_HOLY_SOUND) {
      this->holySound.playSound(0);
      this->holySoundPlayed = true;
    }

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