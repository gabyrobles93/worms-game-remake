#include "sprite_animation.h"

View::SpriteAnimation::SpriteAnimation(SDL_Renderer * r) : renderer(r) {
  this->running = false;
}

View::SpriteAnimation::~SpriteAnimation() {

}

void View::SpriteAnimation::run() {
  this->running = true;
  int clipWidth = this->currentSpriteSheet->getWidth();
  int clipHeight = clipWidth;
  int numClips = this->currentSpriteSheet->getHeight() / clipWidth;
  int fpc = 50;
  while (this->running) {
    // Ida
    for (int i = 0 ; i < numClips * fpc && this->running; i++) {
      SDL_SetRenderDrawColor( this->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
      SDL_RenderClear( this->renderer );
      SDL_Rect currentClip = {
        0,
        0 + (i / fpc ) * clipHeight,
        clipWidth,
        clipHeight
      };
      //std::cout << "SDL RECT Y " << currentClip.y << std::endl;
      //std::cout << "i % fpc: " << i << " mod " << fpc << " " << i%fpc << std::endl;
      this->currentSpriteSheet->render(
        this->renderer,
        this->currentSpriteSheet->getX(),
        this->currentSpriteSheet->getY(),
        &currentClip);

      SDL_RenderPresent(this->renderer);
    }
    
    // Y vuelta
    for (int i = numClips * fpc ; i >= 0 && this->running ; i--) {
      SDL_SetRenderDrawColor( this->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
      SDL_RenderClear( this->renderer );
      SDL_Rect currentClip = {
        0,
        0 + (i / fpc ) * clipHeight,
        clipWidth,
        clipHeight
      };
      //std::cout << "SDL RECT Y " << currentClip.y << std::endl;
      //std::cout << "i % fpc: " << i << " mod " << fpc << " " << i%fpc << std::endl;
      this->currentSpriteSheet->render(
        this->renderer,
        this->currentSpriteSheet->getX(),
        this->currentSpriteSheet->getY(),
        &currentClip);

      SDL_RenderPresent(this->renderer);
    }
  }

  this->running = false;
}

void View::SpriteAnimation::setSpriteSheet(Texture * newTexture) {
  if (!this->running) {
    this->currentSpriteSheet = newTexture;
  }
}

void View::SpriteAnimation::stopAnimation(void) {
  this->running = false;
}

bool View::SpriteAnimation::isRunning(void) const {
  return this->running;
}

size_t View::SpriteAnimation::getId(void) const {
    return 0;
}