#include "breathing.h"

View::Breathing::Breathing(View::Worm * worm, SDL_Renderer * r) {
  this->state = WS_BREATHING;
  this->context = worm;
  this->textures[NONE].loadFromFile(gPath.PATH_WORM_BREATH_1, r);
  this->textures[UP].loadFromFile(gPath.PATH_WORM_BREATH_1_UP, r);
  this->textures[DOWN].loadFromFile(gPath.PATH_WORM_BREATH_1_DOWN, r);
  this->sprites[NONE].setSpriteSheet(&this->textures[NONE]);
  this->sprites[UP].setSpriteSheet(&this->textures[UP]);
  this->sprites[DOWN].setSpriteSheet(&this->textures[DOWN]);
}

View::Breathing::~Breathing() {

}

void View::Breathing::render(SDL_Renderer * r, int camX, int camY, worm_inclination_t incl, bool mirrored, int angle) {
  SDL_Rect clip = this->sprites[incl].getNextClip();
  View::Texture & current = this->textures[incl];
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

void View::Breathing::resetAnimation(void) {
  std::map<worm_inclination_t, SpriteAnimation>::iterator it = this->sprites.begin();
  for (; it != this->sprites.end() ; it++) {
    it->second.reset();
  }
}