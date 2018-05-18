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

void View::Girder::render(SDL_Renderer * renderer, int x, int y) {
  Texture & current = this->currentTexture;
  current.render(renderer, x - current.getWidth() / 2, y - current.getHeight() / 2);
}

degrees_t View::Girder::getCurrentDegrees(void) {
  return (degrees_t)this->currentDegrees;
}

int View::Girder::getWidth(void) {
  return this->currentTexture.getWidth();
}

int View::Girder::getHeight(void) {
  return this->currentTexture.getHeight();
}

int View::Girder::getX(void) {
  return this->currentTexture.getX();
}

int View::Girder::getY(void) {
  return this->currentTexture.getY();
}