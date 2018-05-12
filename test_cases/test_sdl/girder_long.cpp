#include "girder_long.h"

View::GirderShort::GirderShort(SDL_Renderer * renderer) {
  this->textures[NINETY_DEGREES].loadFromFile("girder_images/grdl0.png", renderer);
  this->textures[SIXTY_DEGREES].loadFromFile("girder_images/grdl1.png", renderer);
  this->textures[FORTYFIVE_DEGREES].loadFromFile("girder_images/grdl2.png", renderer);
  this->textures[THIRTY_DEGREES].loadFromFile("girder_images/grdl3.png", renderer);
  this->textures[ZERO_DEGREES].loadFromFile("girder_images/grdl4.png", renderer);
  this->textures[NEGATIVE_THIRTY_DEGREES].loadFromFile("girder_images/grdl5.png", renderer);
  this->textures[NEGATIVE_FORTYFIVE_DEGREES].loadFromFile("girder_images/grdl6.png", renderer);
  this->textures[NEGATIVE_SIXTY_DEGREES].loadFromFile("girder_images/grdl7.png", renderer);
  this->textures[NEGATIVE_NINETY_DEGREES].loadFromFile("girder_images/grdl8.png", renderer);

  this->currentTexture = this->textures[ZERO_DEGREES];
  this->currentDegrees = ZERO_DEGREES;
}

View::GirderShort::~GirderShort() {}
