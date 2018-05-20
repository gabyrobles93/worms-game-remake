#include <SDL2/SDL.h>
#include <string>
#include "worm.h"

View::Worm::Worm(SDL_Renderer * r, std::string name, size_t team, int health) :
  currentSprite(r),
  name(name),
  team(team),
  health(health) {
  this->textures[PLAIN_WORM].loadFromFile(PATH_PLAIN_WORM, r);

  this->textures[BREATH_1].loadFromFile(PATH_WORM_BREATH_1, r);
  this->textures[BREATH_1_UP].loadFromFile(PATH_WORM_BREATH_1_UP, r);
  this->textures[BREATH_1_DOWN].loadFromFile(PATH_WORM_BREATH_1_DOWN, r);

  this->textures[WALK].loadFromFile(PATH_WORM_WALK, r);
  this->textures[WALK_UP].loadFromFile(PATH_WORM_WALK_UP, r);
  this->textures[WALK_DOWN].loadFromFile(PATH_WORM_WALK_DOWN, r);

  this->currentSprite.setSpriteSheet(&this->textures[BREATH_1]);
  this->currentAnimation = PLAIN_WORM;
  this->mirrored = false;
  this->alive = true;
  // this->currentSprite.start();

  this->x = 0;
  this->y = 0;
}

View::Worm::~Worm() {
  if (this->currentSprite.isRunning()) {
    this->currentSprite.stopAnimation();
    this->currentSprite.join();
  }
  
}

/* void View::Worm::handleEvent(SDL_Event & event) {
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

} */

int View::Worm::getWidth(void) const {
  std::map<worm_animation_t, Texture>::const_iterator it = this->textures.find(this->currentAnimation);
  return it->second.getWidth();
}

int View::Worm::getHeight(void) const {
  std::map<worm_animation_t, Texture>::const_iterator it = this->textures.find(this->currentAnimation);
  return it->second.getHeight();
}

int View::Worm::getX(void) const {
  //std::map<worm_animation_t, Texture>::const_iterator it = this->textures.find(this->currentAnimation);
  //return it->second.getX();
  return this->x;
}

int View::Worm::getY(void) const { 
  /*std::map<worm_animation_t, Texture>::const_iterator it = this->textures.find(this->currentAnimation);
  return it->second.getY();*/
  return this->y;
}

void View::Worm::setX(int x) {
  this->textures[this->currentAnimation].setX(x);
  this->x = x;
}

void View::Worm::setY(int y) {
  this->textures[this->currentAnimation].setY(y);
  this->y = y;
}

void View::Worm::render(SDL_Renderer * r, int camX, int camY) {
  Texture & current = this->textures[this->currentAnimation];
  if (this->mirrored) {
    current.render(
      r, 
      this->x - (current.getWidth() / 2) - camX, 
      this->y - (current.getHeight() / 2) - camY, 
      NULL, 
      0, 
      NULL, 
      SDL_FLIP_HORIZONTAL
    );
  } else {
    current.render(
      r, 
      this->x - (current.getWidth() / 2) - camX, 
      this->y - (current.getHeight() / 2) - camY
    );
  }
  
}

void View::Worm::setHealth(int newHealth) {
  this->health = newHealth;
}

int View::Worm::getHealth(void) {
  return this->health;
}

bool View::Worm::isAlive(void) {
  return this->alive;
}