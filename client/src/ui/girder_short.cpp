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
    this->currentIndexDegrees = index[degrees];
    this->currentTexture = this->textures[degrees];
  } else {
    this->currentIndexDegrees = 4; // Harcoded
    this->currentTexture = this->textures[this->getCurrentDegrees()];
  }
    
  this->x = 0;
  this->y = 0;
}

View::GirderShort::~GirderShort() {}
