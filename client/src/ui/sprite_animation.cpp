#include "sprite_animation.h"

View::SpriteAnimation::SpriteAnimation(size_t fpc) : fpc(fpc) {
  this->reverse = false;
  this->counter = 0;
}

View::SpriteAnimation::~SpriteAnimation() {}

// Funciona y no le deseo a nadie que tenga
// que intentar de entender como es que funciona
// y mucho menos tener que debuggear este metodo.
SDL_Rect View::SpriteAnimation::getNextClip(void) {
  if (this->reverse == false) {
    if (this->counter < this->numClips * this->fpc) {
      SDL_Rect currentClip = {
          0,
          0 + (this->counter / this->fpc ) * this->clipHeight,
          this->clipWidth,
          this->clipHeight
      };
      this->counter++;
      return currentClip;
    }

    this->reverse = true;
    this->counter = ((this->numClips - 1) * fpc) - 1;
  }

  if (this->reverse == true) {
    if (this->counter >= this->fpc) {
      SDL_Rect currentClip = {
          0,
          0 + (this->counter / this->fpc ) * this->clipHeight,
          this->clipWidth,
          this->clipHeight
      };
      this->counter--;
      return currentClip;
    }

    this->counter = 0;
    this->reverse = false;
  }

  SDL_Rect secondClip = {
    0,
    0 + (this->counter / this->fpc ) * this->clipHeight,
    this->clipWidth,
    this->clipHeight
  };

  this->counter++;
  return secondClip;
}

void View::SpriteAnimation::setSpriteSheet(Texture * newTexture) {
  this->currentSpriteSheet = newTexture;
  this->clipWidth = this->currentSpriteSheet->getWidth();
  this->clipHeight = clipWidth;
  this->numClips = this->currentSpriteSheet->getHeight() / clipWidth;
  this->reverse = false;
  this->counter = 0;
}
