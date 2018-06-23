#include "walking.h"

View::Walking::Walking(View::Worm * worm, SDL_Renderer * r) {
  this->state = WS_WALKING;
  this->context = worm;
  this->textures[NONE].loadFromFile(gPath.PATH_WORM_WALK, r);
  this->textures[UP].loadFromFile(gPath.PATH_WORM_WALK_UP, r);
  this->textures[DOWN].loadFromFile(gPath.PATH_WORM_WALK_DOWN, r);
  this->sprites[NONE].setSpriteSheet(&this->textures[NONE]);
  this->sprites[UP].setSpriteSheet(&this->textures[UP]);
  this->sprites[DOWN].setSpriteSheet(&this->textures[DOWN]);
  this->walkingSound.setSound(gPath.PATH_SOUND_WORM_WALKING);
  this->walkingExpandSound.setSound(gPath.PATH_SOUND_WORM_WALKING_EXPAND);
  this->playedExpand = true;
}

View::Walking::~Walking() {
  this->walkingSound.stopSound();
}

void View::Walking::render(SDL_Renderer * r, int camX, int camY, worm_inclination_t incl, bool mirrored, int angle) {
  if (!this->walkingExpandSound.isPlaying() && !this->walkingSound.isPlaying()) {
    if (this->playedExpand) {
      this->walkingSound.playSound(0);
      this->playedExpand = false;
    } else {
      this->walkingExpandSound.playSound(0);
      this->playedExpand = true;
    }
  }
  
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

void View::Walking::resetAnimation(void) {
  std::map<worm_inclination_t, SpriteAnimation>::iterator it = this->sprites.begin();
  for (; it != this->sprites.end() ; it++) {
    it->second.reset();
  }
}