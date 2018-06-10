#include "sprite_animation.h"

View::SpriteAnimation::SpriteAnimation(size_t fpc, sprite_type_t type) : 
  fpc(fpc) {
  this->type = type;
  this->reverse = false;
  this->counter = 0;
  this->finish = false;
}

View::SpriteAnimation::~SpriteAnimation() {}

// Funciona y no le deseo a nadie que tenga
// que intentar de entender como es que funciona
// y mucho menos tener que debuggear este metodo.
SDL_Rect View::SpriteAnimation::getNextClip(int grades) {
  switch (this->type) {
    case INFINITE_GOING_AND_BACK:
      return this->getNextClipInfiniteRoundTrip();
      break;
    case ONLY_GOING:
      return this->getNextClipOnlyGoing();
      break;
    case INFINITE_GOING:
      return this->getNextClipInfiniteGoing();
      break;
    case DEPENDENT_ON_GRADES:
      return this->getNextClipDependentOnGrades(grades);
      break;
    default:
      return {0, 0, 0, 0};
  }
}

void View::SpriteAnimation::setSpriteSheet(Texture * newTexture) {
  this->currentSpriteSheet = newTexture;
  this->clipWidth = this->currentSpriteSheet->getWidth();
  this->clipHeight = clipWidth;
  this->numClips = this->currentSpriteSheet->getHeight() / clipWidth;
  this->reverse = false;
  this->counter = 0;
}

SDL_Rect View::SpriteAnimation::getNextClipInfiniteRoundTrip(void) {
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

SDL_Rect View::SpriteAnimation::getNextClipOnlyGoing(void) {
  SDL_Rect currentClip = {
    0,
    0 + (this->counter / this->fpc ) * this->clipHeight,
    this->clipWidth,
    this->clipHeight
  };

  if (this->counter < this->numClips * this->fpc) {
    this->counter++;
  } else {
    this->finish = true;
  }

  return currentClip;
}

SDL_Rect View::SpriteAnimation::getNextClipInfiniteGoing(void) {
  SDL_Rect currentClip = {
    0,
    0 + (this->counter / this->fpc ) * this->clipHeight,
    this->clipWidth,
    this->clipHeight
  };

  if (this->counter < this->numClips * this->fpc) {
    this->counter++;
  } else {
    this->counter = 0;
    currentClip = {
      0,
      0 + (this->counter / this->fpc ) * this->clipHeight,
      this->clipWidth,
      this->clipHeight
    };
  }

  return currentClip;
}

SDL_Rect View::SpriteAnimation::getNextClipDependentOnGrades(int grades) {
  int numClip = (grades * this->numClips) / 360;
  SDL_Rect currentClip = {
    0,
    0 + numClip * this->clipHeight,
    this->clipWidth,
    this->clipHeight
  };

  return currentClip;
}

bool View::SpriteAnimation::finished(void) {
  return this->finish;
}
