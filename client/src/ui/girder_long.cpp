#include "girder_long.h"

View::GirderLong::GirderLong(SDL_Renderer * renderer, int degrees) {
  this->textures[NINETY_DEGREES].loadFromFile(PATH_GIRDER_LONG_90, renderer);
  this->textures[SIXTY_DEGREES].loadFromFile(PATH_GIRDER_LONG_60, renderer);
  this->textures[FORTYFIVE_DEGREES].loadFromFile(PATH_GIRDER_LONG_45, renderer);
  this->textures[THIRTY_DEGREES].loadFromFile(PATH_GIRDER_LONG_30, renderer);
  this->textures[ZERO_DEGREES].loadFromFile(PATH_GIRDER_LONG_0, renderer);
  this->textures[NEGATIVE_THIRTY_DEGREES].loadFromFile(PATH_GIRDER_LONG_NEGATIVE_30, renderer);
  this->textures[NEGATIVE_FORTYFIVE_DEGREES].loadFromFile(PATH_GIRDER_LONG_NEGATIVE_45, renderer);
  this->textures[NEGATIVE_SIXTY_DEGREES].loadFromFile(PATH_GIRDER_LONG_NEGATIVE_60, renderer);
  this->textures[NEGATIVE_NINETY_DEGREES].loadFromFile(PATH_GIRDER_LONG_NEGATIVE_90, renderer);

  if (degrees != ZERO_DEGREES) {
    this->currentDegrees = degrees;
  } else {
    this->currentDegrees = ZERO_DEGREES;
  }

  this->currentTexture = this->textures[this->currentDegrees];
}

View::GirderLong::~GirderLong() {}
