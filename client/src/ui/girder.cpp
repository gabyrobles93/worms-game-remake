#include "girder.h"

View::Girder::~Girder(void) {
}

void View::Girder::rotateClockwise(void) {
  // Si no es -90 grados
  if (this->currentIndexDegrees != DIFF_POS-1) {
    this->currentIndexDegrees++;
  } else {
    // Cambia a +60 grados
    this->currentIndexDegrees = 1;
  }
  this->currentTexture = this->textures[this->getCurrentDegrees()];
}

void View::Girder::rotateCounterClockwise(void) {
  // Si no es +90 grados
  if (this->currentIndexDegrees) {
    this->currentIndexDegrees--;
  } else {
    // Cambia a -60 grados
    this->currentIndexDegrees = DIFF_POS-2;
  }
  this->currentTexture = this->textures[this->getCurrentDegrees()];
}

void View::Girder::render(SDL_Renderer * renderer, int camX, int camY) {
  Texture & current = this->currentTexture;
  current.render(renderer, this->x - camX, this->y - camY);
}

degrees_t View::Girder::getCurrentDegrees(void) {
  degrees_t vec[] = {
    NINETY_DEGREES,
    SIXTY_DEGREES,
    FORTYFIVE_DEGREES,
    THIRTY_DEGREES,
    ZERO_DEGREES,
    NEGATIVE_THIRTY_DEGREES,
    NEGATIVE_FORTYFIVE_DEGREES,
    NEGATIVE_SIXTY_DEGREES,
    NEGATIVE_NINETY_DEGREES
  };
  return vec[this->currentIndexDegrees];
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
  this->x = x - (this->currentTexture.getWidth() / 2);
}

void View::Girder::setY(int y) {
  this->currentTexture.setY(y);
  this->y = y - (this->currentTexture.getHeight() / 2);
}