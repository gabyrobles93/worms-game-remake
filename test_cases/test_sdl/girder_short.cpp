#include "girder_short.h"

View::GirderShort::GirderShort(SDL_Renderer * renderer) {
  this->textures[NINETY_DEGREES].loadFromFile("girder_images/grds0.png", renderer);
  this->textures[SIXTY_DEGREES].loadFromFile("girder_images/grds1.png", renderer);
  this->textures[FORTYFIVE_DEGREES].loadFromFile("girder_images/grds2.png", renderer);
  this->textures[THIRTY_DEGREES].loadFromFile("girder_images/grds3.png", renderer);
  this->textures[ZERO_DEGREES].loadFromFile("girder_images/grds4.png", renderer);
  this->textures[NEGATIVE_THIRTY_DEGREES].loadFromFile("girder_images/grds5.png", renderer);
  this->textures[NEGATIVE_FORTYFIVE_DEGREES].loadFromFile("girder_images/grds6.png", renderer);
  this->textures[NEGATIVE_SIXTY_DEGREES].loadFromFile("girder_images/grds7.png", renderer);
  this->textures[NEGATIVE_NINETY_DEGREES].loadFromFile("girder_images/grds8.png", renderer);

  this->currentTexture = this->textures[ZERO_DEGREES];
  this->currentDegrees = ZERO_DEGREES;
}

View::GirderShort::~GirderShort() {}
