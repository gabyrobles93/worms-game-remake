#include "falling.h"

View::Falling::Falling(View::Worm * worm, SDL_Renderer * r) {
  this->state = WS_FALLING;
  this->context = worm;
  this->texture.loadFromFile(gPath.PATH_WORM_ROLL, r);
  this->sprite.setSpriteSheet(&this->texture);
  this->sprite.changeSpriteType(INFINITE_GOING);
}

View::Falling::~Falling() {

}

void View::Falling::render(SDL_Renderer * r, int camX, int camY, worm_inclination_t incl, bool mirrored) {
  SDL_Rect clip = this->sprite.getNextClip();
  View::Texture & current = this->texture;
  if (mirrored) {
    current.render(
      r, 
      this->context->getX() - current.getWidth() / 2 - camX, 
      this->context->getY() - current.getWidth() / 2 - camY, 
      &clip, 
      0, 
      NULL, 
      SDL_FLIP_HORIZONTAL
    );
  } else {
    current.render(
      r, 
      this->context->getX() - current.getWidth() / 2 - camX, 
      this->context->getY() - current.getWidth() / 2 - camY, 
      &clip
    );
  }
  
}