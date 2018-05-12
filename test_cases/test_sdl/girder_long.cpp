#include "girder_long.h"

View::GirderLong::GirderLong(SDL_Renderer * renderer, degrees_t degrees) {
  this->textures[NINETY_DEGREES].loadFromFile("../images/grdl0.png", renderer);
  this->textures[SIXTY_DEGREES].loadFromFile("../images/grdl1.png", renderer);
  this->textures[FORTYFIVE_DEGREES].loadFromFile("../images/grdl2.png", renderer);
  this->textures[THIRTY_DEGREES].loadFromFile("../images/grdl3.png", renderer);
  this->textures[ZERO_DEGREES].loadFromFile("../images/grdl4.png", renderer);
  this->textures[NEGATIVE_THIRTY_DEGREES].loadFromFile("../images/grdl5.png", renderer);
  this->textures[NEGATIVE_FORTYFIVE_DEGREES].loadFromFile("../images/grdl6.png", renderer);
  this->textures[NEGATIVE_SIXTY_DEGREES].loadFromFile("../images/grdl7.png", renderer);
  this->textures[NEGATIVE_NINETY_DEGREES].loadFromFile("../images/grdl8.png", renderer);

  if (degrees != ZERO_DEGREES) {
    this->currentDegrees = degrees;
  } else {
    this->currentDegrees = ZERO_DEGREES;
  }

  this->currentTexture = this->textures[this->currentDegrees];
}

View::GirderLong::~GirderLong() {}
