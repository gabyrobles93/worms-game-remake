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
  this->currentTexture.render(renderer, x, y);
}
