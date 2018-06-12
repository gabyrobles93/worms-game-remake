#include "cluster.h"

#define CLUSTER_FPC 3

View::Cluster::Cluster(SDL_Renderer * r, int countdown, int ratioExplosion) : 
	sprite(CLUSTER_FPC, INFINITE_GOING),
	explosion(r, ratioExplosion, "Grenade"),
	countdownText(COUNTDOWN_TEXT_SIZE) {
  this->texture.loadFromFile(gPath.PATH_CLUSTER, r);
  this->sprite.setSpriteSheet(&this->texture);

	this->exploded = false;
	this->finished = false;
	this->playedAboutToExplode = false;

	this->sound.setSound(gPath.PATH_SOUND_THROW_PROJECTIL);
  this->sound.playSound(0);
	this->countdown = countdown;
	this->ratioExplosion = ratioExplosion;
}

View::Cluster::~Cluster() {

}

void View::Cluster::render(SDL_Renderer * r, int camX, int camY) {
	if (!this->exploded) {
		// Render Cluster animation
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