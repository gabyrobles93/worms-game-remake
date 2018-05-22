#include <SDL2/SDL.h>
#include <string>
#include "worm.h"

#define PADDING 1

View::Worm::Worm(SDL_Renderer * r, std::string name, size_t team, int health) :
  currentSprite(r),
  name(name),
  team(team),
  health(health),
  font(PATH_FONT_ARIAL_BOLD, 14) {
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

  this->nameText.loadFromRenderedText(r, this->font, this->name, colors[this->team]);
  this->healthText.loadFromRenderedText(r, this->font, std::to_string(this->health), colors[this->team]);
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
  Texture & current = this->textures[this->currentAnimation];
  current.setX(x);
  this->x = x - (current.getWidth() / 2);
}

void View::Worm::setY(int y) {
  Texture & current = this->textures[this->currentAnimation];
  current.setY(y);
  this->y = y - (current.getHeight() / 2);
}

void View::Worm::render(SDL_Renderer * r, int camX, int camY) {
  Texture & current = this->textures[this->currentAnimation];
  if (this->mirrored) {
    current.render(
      r, 
      this->x - camX, 
      this->y - camY, 
      NULL, 
      0, 
      NULL, 
      SDL_FLIP_HORIZONTAL
    );
  } else {
    current.render(
      r, 
      this->x - camX, 
      this->y - camY
    );
  }
  
  // Display de la data
  //Render health
  SDL_Rect fillRect = { 
    this->x + (current.getWidth() - this->healthText.getWidth()) / 2  - camX - PADDING, 
    this->y - this->healthText.getHeight() / 2 - camY - PADDING, 
    this->healthText.getWidth() + PADDING * 2, 
    this->healthText.getHeight() + PADDING * 2
  };
  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xFF );        
  SDL_RenderFillRect(r, &fillRect);

  this->healthText.render(
    r, 
    this->x + (current.getWidth() - this->healthText.getWidth()) / 2 - camX, 
    this->y - this->healthText.getHeight() / 2 - camY
  );

  // Render name
  SDL_Rect fillRectName = { 
    this->x + (current.getWidth() - this->nameText.getWidth()) / 2  - camX - PADDING, 
    this->y - this->healthText.getHeight() - this->nameText.getHeight() / 2 - camY - PADDING - PADDING * 2, 
    this->nameText.getWidth() + PADDING * 2, 
    this->nameText.getHeight() + PADDING * 2
  };

  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xFF );        
  SDL_RenderFillRect(r, &fillRectName);
  
  this->nameText.render(
    r, 
    this->x + (current.getWidth() - this->nameText.getWidth()) / 2  - camX, 
    this->y - this->healthText.getHeight() - this->nameText.getHeight() / 2 - camY - PADDING * 2
  );
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