#include "water.h"

View::Water::Water() {}

View::Water::~Water() {}

void View::Water::init(SDL_Renderer * r, int x, int y, int levelWidth, int levelHeight, const char * patterPath) {
  this->x = x;
  this->y = y;
  this->width = levelWidth;
  this->height = levelHeight - y;
  
  if (patterPath) {
    this->texture.loadFromFile(patterPath, r);
  } else {
    this->texture.loadFromFile(gPath.PATH_WATER_DEFAULT, r);
  } 
}

void View::Water::render(SDL_Renderer * r, int camX, int camY) {
  int tileWidth = this->texture.getWidth();
  int tileHeight = this->texture.getHeight();
  for (int x = 0 ; x <= this->width / tileWidth ; x++) {
    for (int y = 0 ; y <= this->height / tileHeight ; y++) {
      this->texture.render(
        r, 
        this->x + x * tileWidth - camX, 
        this->y + y * tileHeight - camY);
    }    
  }
}

int View::Water::getWidth(void) const {
  return this->width;
}
int View::Water::getHeight(void) const {
  return this->height;
}

int View::Water::getX(void) const {
  return this->x;
}

int View::Water::getY(void) const {
  return this->y;
}

void View::Water::setX(int x) {
  this->x = x;
}

void View::Water::setY(int y) {
  this->y = y;
}