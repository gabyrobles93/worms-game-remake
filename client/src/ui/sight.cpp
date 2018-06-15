#include "sight.h"

#define SIGHT_FPC 3

View::Sight::Sight(SDL_Renderer * r, int ratio, int angle) :
  sprite(SIGHT_FPC, INFINITE_GOING_AND_BACK) {
  this->texture.loadFromFile(gPath.PATH_DEFAULT_SIGHT, r);
  this->ratio = ratio;
  this->angle = angle;

  this->sprite.setSpriteSheet(&this->texture);
}

View::Sight::~Sight() {

}

int View::Sight::getWidth(void) const {
	return this->width;
}

int View::Sight::getHeight(void) const {
	return this->height;
}

int View::Sight::getX(void) const {
	return this->x;
}

int View::Sight::getY(void) const {
	return this->y;
}

void View::Sight::setX(int x) {
	this->x = x - this->texture.getWidth() / 2;
}

void View::Sight::setY(int y) {
	this->y = y - this->texture.getWidth() / 2;
}

void View::Sight::setXYcenter(int xc, int yc) {
  this->xCenter = xc;
  this->yCenter = yc;
}

void View::Sight::setAngle(int a) {
  this->angle = a * DEGTORAD;
}

void View::Sight::setRatio(int r) {
  this->ratio = r;
}

void View::Sight::setMirrored(bool m) {
  this->mirrored = m;
}

void View::Sight::render(SDL_Renderer * r, int camX, int camY) {
  int fct;
  this->mirrored ? fct = 1 : fct = -1;

  SDL_Rect clip = this->sprite.getNextClip();
  int x = xCenter + (int)(this->ratio * cos(this->angle) * fct);
  int y = yCenter - (int)(this->ratio * sin(this->angle));
  this->texture.render(r, x - this->texture.getWidth() / 2 - camX, y - this->texture.getWidth() / 2 - camY, &clip);
}