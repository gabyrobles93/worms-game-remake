#include "worm.h"

View::Worm::Worm(SDL_Renderer * r) :
  currentSprite(r) {
  this->textures[BREATH_1].loadFromFile("../images/Worms/wbrth1.png", r);
  this->textures[BREATH_1_UP].loadFromFile("../images/Worms/wbrth1u.png", r);
  this->textures[BREATH_1_DOWN].loadFromFile("../images/Worms/wbrth1d.png", r);

  this->textures[WALK].loadFromFile("../images/Worms/wwalk.png", r);
  this->textures[WALK_UP].loadFromFile("../images/Worms/wwalkd.png", r);
  this->textures[WALK_DOWN].loadFromFile("../images/Worms/wwalku.png", r);

  this->currentSprite.setSpriteSheet(&this->textures[BREATH_1]);
  this->currentAnimation = BREATH_1;
  this->currentSprite.start();
}

View::Worm::~Worm() {
  if (this->currentSprite.isRunning()) {
    this->currentSprite.stopAnimation();
    this->currentSprite.join();
  }
  
}

void View::Worm::handleEvent(SDL_Event & event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_LEFT) {
      this->currentSprite.stopAnimation();
      this->currentSprite.join();
      this->currentAnimation = WALK;
      this->currentSprite.setSpriteSheet(&this->textures[WALK]);
      this->currentSprite.start();
    }
  }
  
  if (event.type == SDL_KEYUP) {
    this->currentSprite.stopAnimation();
    this->currentSprite.join();
    this->currentAnimation = BREATH_1;
    this->currentSprite.setSpriteSheet(&this->textures[BREATH_1]);
    this->currentSprite.start();
  }
  
}

int View::Worm::getWidth(void) {
  return this->textures[this->currentAnimation].getWidth();
}

int View::Worm::getHeight(void) {
  return this->textures[this->currentAnimation].getHeight();
}

int View::Worm::getX(void) {
  return this->textures[this->currentAnimation].getX();
}

int View::Worm::getY(void) { 
  return this->textures[this->currentAnimation].getY();
}

void View::Worm::render(SDL_Renderer * r, int x, int y) {
  return;  
}


