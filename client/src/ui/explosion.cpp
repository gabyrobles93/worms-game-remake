#include "explosion.h"

View::Explosion::Explosion(SDL_Renderer * r, int ratio, std::string weapon) :
  sprite(EXPLOSION_FPC, ONLY_GOING) {
  this->texture.loadFromFile(gPath.PATH_EXPLOSION_EFFECT, r);
  this->width = ratio * 2;
  this->height = retio * 2;
  this->x = 0;
  this->y = 0;
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
  
}