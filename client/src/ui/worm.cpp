#include <SDL2/SDL.h>
#include <string>
#include "worm.h"

#define PADDING 1
#define FPC 3

View::Worm::Worm(SDL_Renderer * r, std::string name, size_t team, int health) :
  sprite(FPC),
  name(name),
  team(team),
  health(health),
  font(PATH_FONT_ARIAL_BOLD, 20) {

  const SDL_Color colors[] = {
    {0, 0, 0, 0},
    {255, 0, 0, 0},
    {0, 255, 0, 0},
    {0, 0, 255, 0}
  };

  this->textures[PLAIN_WORM].loadFromFile(PATH_PLAIN_WORM, r);

  this->textures[BREATH_1].loadFromFile(PATH_WORM_BREATH_1, r);
  this->textures[BREATH_1_UP].loadFromFile(PATH_WORM_BREATH_1_UP, r);
  this->textures[BREATH_1_DOWN].loadFromFile(PATH_WORM_BREATH_1_DOWN, r);

  this->textures[WALK].loadFromFile(PATH_WORM_WALK, r);
  this->textures[WALK_UP].loadFromFile(PATH_WORM_WALK_UP, r);
  this->textures[WALK_DOWN].loadFromFile(PATH_WORM_WALK_DOWN, r);

  this->currentAnimation = BREATH_1;
  this->sprite.setSpriteSheet(&this->textures[this->currentAnimation]);
  
  this->mirrored = false;
  this->alive = true;

  this->x = 0;
  this->y = 0;

  this->nameText.loadFromRenderedText(r, this->font, this->name, colors[this->team]);
  this->healthText.loadFromRenderedText(r, this->font, std::to_string(this->health), colors[this->team]);
}

View::Worm::~Worm() {}

int View::Worm::getWidth(void) const {
  std::map<worm_animation_t, Texture>::const_iterator it = this->textures.find(this->currentAnimation);
  return it->second.getWidth();
}

int View::Worm::getHeight(void) const {
  std::map<worm_animation_t, Texture>::const_iterator it = this->textures.find(this->currentAnimation);
  return it->second.getHeight();
}

int View::Worm::getX(void) const {
  return this->x;
}

int View::Worm::getY(void) const { 
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
  // Uso get width porque el offset es de un solo clip
  // Y los clips de los data sheets son cuadrados
  this->y = y - (current.getWidth() / 2);
}

void View::Worm::render(SDL_Renderer * r, int camX, int camY) {
  Texture & current = this->textures[this->currentAnimation];
  SDL_Rect clip = this->sprite.getNextClip();
  if (this->mirrored) {
    current.render(
      r, 
      this->x - camX, 
      this->y - camY, 
      &clip, 
      0, 
      NULL, 
      SDL_FLIP_HORIZONTAL
    );
  } else {
    current.render(
      r, 
      this->x - camX, 
      this->y - camY,
      &clip
    );
  }
  
  // Display de la data
  this->renderWormData(r, camX, camY);
}

void View::Worm::renderWormData(SDL_Renderer * r, int camX, int camY) {
  Texture & current = this->textures[this->currentAnimation];

  //Render health
  SDL_Rect fillRect = { 
    this->x + (current.getWidth() - this->healthText.getWidth()) / 2 - camX - PADDING, 
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
    this->x + (current.getWidth() - this->nameText.getWidth()) / 2 - camX - PADDING, 
    this->y - this->healthText.getHeight() - this->nameText.getHeight() / 2 - camY - PADDING - PADDING * 2, 
    this->nameText.getWidth() + PADDING * 2, 
    this->nameText.getHeight() + PADDING * 2
  };

  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xFF );        
  SDL_RenderFillRect(r, &fillRectName);
  
  this->nameText.render(
    r, 
    this->x + (current.getWidth() - this->nameText.getWidth()) / 2  - camX, 
    this->y - this->healthText.getHeight() - this->nameText.getHeight() / 2  - camY - PADDING * 2
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