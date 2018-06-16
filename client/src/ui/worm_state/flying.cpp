#include "flying.h"
#define MAX_FLYING_TEXTURES 3

View::Flying::Flying(View::Worm * worm, SDL_Renderer * r) {
  this->state = WS_FLYING;
  this->context = worm;

  const char * sounds[] = {
    gPath.PATH_SOUND_OOFF_1.c_str(),
    gPath.PATH_SOUND_OOFF_2.c_str(),
    gPath.PATH_SOUND_OOFF_3.c_str(),
    gPath.PATH_SOUND_OW_1.c_str(),
    gPath.PATH_SOUND_OW_2.c_str(),
    gPath.PATH_SOUND_OW_3.c_str()
  };
  this->sound.setSound(sounds[rand() % 6]);
  this->sound.playSound(0);

  this->index = 0;
  this->textures[this->index].loadFromFile(gPath.PATH_WORM_FLYING_1, r);
  this->sprites[this->index].setSpriteSheet(&this->textures[this->index]);
  this->sprites[this->index].changeSpriteType(INFINITE_GOING);

  this->index = 1;
  this->textures[this->index].loadFromFile(gPath.PATH_WORM_FLYING_2, r);
  this->sprites[this->index].setSpriteSheet(&this->textures[this->index]);
  this->sprites[this->index].changeSpriteType(INFINITE_GOING);

  this->index = 2;
  this->textures[this->index].loadFromFile(gPath.PATH_WORM_FLYING_3, r);
  this->sprites[this->index].setSpriteSheet(&this->textures[this->index]);
  this->sprites[this->index].changeSpriteType(INFINITE_GOING);

  this->index = 0;
}

View::Flying::~Flying() {

}

void View::Flying::render(SDL_Renderer * r, int camX, int camY, worm_inclination_t incl, bool mirrored) {
  if (!(this->index < MAX_FLYING_TEXTURES)) {
    this->index = 0;
  }
  
  View::SpriteAnimation & currentAnimation = this->sprites[this->index];
  View::Texture & current = this->textures[this->index];
  this->index++;
  SDL_Rect clip = currentAnimation.getNextClip();

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