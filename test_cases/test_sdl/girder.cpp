#include "girder.h"

void View::Girder::rotateClockwise(void) {
  // Si no es -90 grados
  if (this->currentDegrees != DIFF_POS-1) {
    this->currentDegrees++;
  } else {
    // Cambia a +60 grados
    this->currentDegrees = 1;
  }
  this->currentTexture = this->textures[this->currentDegrees];
}

void View::Girder::rotateCounterClockwise(void) {
  // Si no es +90 grados
  if (this->currentDegrees) {
    this->currentDegrees--;
  } else {
    // Cambia a -60 grados
    this->currentDegrees = DIFF_POS-2;
  }
  this->currentTexture = this->textures[this->currentDegrees];
}

void View::Girder::render(SDL_Renderer * renderer, int camX, int camY) {
  Texture & current = this->currentTexture;
  current.render(renderer, this->x - (current.getWidth() / 2) - camX, this->y - (current.getHeight() / 2) - camY);
}

degrees_t View::Girder::getCurrentDegrees(void) {
  return (degrees_t)this->currentDegrees;
}

int View::Girder::getWidth(void) const {
  return this->currentTexture.getWidth();
}

int View::Girder::getHeight(void) const {
  return this->currentTexture.getHeight();
}

int View::Girder::getX(void) const {
  return this->x;
}

int View::Girder::getY(void) const {
  return this->y;
}

void View::Girder::setX(int x) {
  this->currentTexture.setX(x);
  this->x = x;
}

void View::Girder::setY(int y) {
  this->currentTexture.setY(y);
  this->y = y;
}