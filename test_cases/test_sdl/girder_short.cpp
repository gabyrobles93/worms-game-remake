#include "girder_short.h"

View::GirderShort::GirderShort(SDL_Renderer * renderer, degrees_t degrees) {
  this->textures[NINETY_DEGREES].loadFromFile("../images/grds0.png", renderer);
  this->textures[SIXTY_DEGREES].loadFromFile("../images/grds1.png", renderer);
  this->textures[FORTYFIVE_DEGREES].loadFromFile("../images/grds2.png", renderer);
  this->textures[THIRTY_DEGREES].loadFromFile("../images/grds3.png", renderer);
  this->textures[ZERO_DEGREES].loadFromFile("../images/grds4.png", renderer);
  this->textures[NEGATIVE_THIRTY_DEGREES].loadFromFile("../images/grds5.png", renderer);
  this->textures[NEGATIVE_FORTYFIVE_DEGREES].loadFromFile("../images/grds6.png", renderer);
  this->textures[NEGATIVE_SIXTY_DEGREES].loadFromFile("../images/grds7.png", renderer);
  this->textures[NEGATIVE_NINETY_DEGREES].loadFromFile("../images/grds8.png", renderer);

  if (degrees != ZERO_DEGREES) {
    this->currentDegrees = degrees;
  } else {
    this->currentDegrees = ZERO_DEGREES;
  }

  this->currentTexture = this->textures[this->currentDegrees];
}

View::GirderShort::~GirderShort() {}
