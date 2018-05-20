#include "girder_short.h"

View::GirderShort::GirderShort(SDL_Renderer * renderer, int degrees) {
  this->textures[NINETY_DEGREES].loadFromFile(PATH_GIRDER_SHORT_90, renderer);
  this->textures[SIXTY_DEGREES].loadFromFile(PATH_GIRDER_SHORT_60, renderer);
  this->textures[FORTYFIVE_DEGREES].loadFromFile(PATH_GIRDER_SHORT_45, renderer);
  this->textures[THIRTY_DEGREES].loadFromFile(PATH_GIRDER_SHORT_30, renderer);
  this->textures[ZERO_DEGREES].loadFromFile(PATH_GIRDER_SHORT_0, renderer);
  this->textures[NEGATIVE_THIRTY_DEGREES].loadFromFile(PATH_GIRDER_SHORT_NEGATIVE_30, renderer);
  this->textures[NEGATIVE_FORTYFIVE_DEGREES].loadFromFile(PATH_GIRDER_SHORT_NEGATIVE_45, renderer);
  this->textures[NEGATIVE_SIXTY_DEGREES].loadFromFile(PATH_GIRDER_SHORT_NEGATIVE_60, renderer);
  this->textures[NEGATIVE_NINETY_DEGREES].loadFromFile(PATH_GIRDER_SHORT_NEGATIVE_90, renderer);

  if (degrees != ZERO_DEGREES) {
    this->currentDegrees = degrees;
  } else {
    this->currentDegrees = ZERO_DEGREES;
  }

  this->currentTexture = this->textures[this->currentDegrees];
  this->x = 0;
  this->y = 0;
}

View::GirderShort::~GirderShort() {}
