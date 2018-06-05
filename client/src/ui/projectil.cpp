#include "projectil.h"

View::Projectil::~Projectil(void) {
}

int View::Projectil::getWidth(void) const {
  return this->texture.getWidth();
}

int View::Projectil::getHeight(void) const {
  return this->texture.getWidth();
}

int View::Projectil::getX(void) const {
  return this->x;
}

int View::Projectil::getY(void) const {
  return this->y;
}

void View::Projectil::setX(int x) {
  this->x = x - (this->texture.getWidth() / 2);
}

void View::Projectil::setY(int y) {
  this->y = y - (this->texture.getWidth() / 2);
}

bool View::Projectil::hasExploded(void) const {
  return this->exploded;
}

bool View::Projectil::hasFinished(void) const {
  return this->finished;
}

void View::Projectil::setExplode(bool exploded) {
  this->exploded = exploded;
}

void View::Projectil::setCountdown(int newCount) {
  this->countdown = newCount;
}