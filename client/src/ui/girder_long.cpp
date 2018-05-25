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

  std::map<int, size_t> index;
  index[NINETY_DEGREES] = 0;
  index[SIXTY_DEGREES] = 1;
  index[FORTYFIVE_DEGREES] = 2;
  index[THIRTY_DEGREES] = 3;
  index[ZERO_DEGREES] = 4;
  index[NEGATIVE_THIRTY_DEGREES] = 5;
  index[NEGATIVE_FORTYFIVE_DEGREES] = 6;
  index[NEGATIVE_SIXTY_DEGREES] = 7;
  index[NEGATIVE_NINETY_DEGREES] = 8;

  if (degrees != ZERO_DEGREES) {
    this->currentDegrees = index[degrees];
    this->currentTexture = this->textures[degrees];
  } else {
    this->currentDegrees = ZERO_DEGREES;
    this->currentTexture = this->textures[this->currentDegrees];
  }  

  this->x = 0;
  this->y = 0;
}

View::GirderLong::~GirderLong() {}
