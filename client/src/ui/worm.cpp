#include <SDL2/SDL.h>
#include <string>
#include "worm.h"

#define PADDING 1
#define FPC 2

View::Worm::Worm(SDL_Renderer * r, std::string name, size_t team, int health) :
  sprite(FPC),
  sight(r),
  name(name),
  team(team),
  health(health),
  font(gPath.PATH_FONT_ARIAL_BOLD, 20) {

  const SDL_Color colors[] = {
    {0, 0, 0, 0},
    {255, 0, 0, 0},
    {0, 255, 0, 0},
    {0, 0, 255, 0}
  };

  this->textures[PLAIN_WORM].loadFromFile(gPath.PATH_PLAIN_WORM, r);

  this->textures[BREATH_1].loadFromFile(gPath.PATH_WORM_BREATH_1, r);
  this->textures[BREATH_1_UP].loadFromFile(gPath.PATH_WORM_BREATH_1_UP, r);
  this->textures[BREATH_1_DOWN].loadFromFile(gPath.PATH_WORM_BREATH_1_DOWN, r);

  this->textures[WALK].loadFromFile(gPath.PATH_WORM_WALK, r);
  this->textures[WALK_UP].loadFromFile(gPath.PATH_WORM_WALK_UP, r);
  this->textures[WALK_DOWN].loadFromFile(gPath.PATH_WORM_WALK_DOWN, r);

  this->textures[ROLL].loadFromFile(gPath.PATH_WORM_ROLL, r);

  this->textures[FALLDN].loadFromFile(gPath.PATH_WORM_FALL_DN, r);

  this->currentAnimation = BREATH_1;
  this->sprite.setSpriteSheet(&this->textures[this->currentAnimation]);
  
  this->mirrored = false;
  this->walking = false;
  this->alive = true;
  this->falling = false;
  this->protagonic = false;

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
  if (this->walking) {
    if (this->currentAnimation != WALK) {
      this->currentAnimation = WALK;
      this->sprite.setSpriteSheet(&this->textures[this->currentAnimation]);
    }
  } else if (this->falling) {
    if (this->currentAnimation != ROLL) {
      this->currentAnimation = ROLL;
      this->sprite.setSpriteSheet(&this->textures[this->currentAnimation]);
    }
  } else {
    if (this->currentAnimation != BREATH_1) {
      this->currentAnimation = BREATH_1;
      this->sprite.setSpriteSheet(&this->textures[this->currentAnimation]);
    }    
  }

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

  // Display sight if protagonic
  if (this->protagonic) {
    this->sight.setXYcenter(this->x, this->y);
    this->sight.setMirrored(this->mirrored);
    this->sight.render(r, camX, camY);
  }
}

void View::Worm::renderWormData(SDL_Renderer * r, int camX, int camY) {

  const SDL_Color colors[] = {
    {0, 0, 0, 0},
    {255, 0, 0, 0},
    {0, 255, 0, 0},
    {0, 0, 255, 0}
  };

  Texture & current = this->textures[this->currentAnimation];

  this->healthText.loadFromRenderedText(r, this->font, std::to_string(this->health), colors[this->team]);
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
  if (this->health <= 0) {
    this->alive = false;
  }
}

int View::Worm::getHealth(void) {
  return this->health;
}

bool View::Worm::isAlive(void) {
  return this->alive;
}

void View::Worm::setMirrored(bool mirr) {
  this->mirrored = mirr;
}

void View::Worm::setWalking(bool walk) {
  this->walking = walk;
}

void View::Worm::setFalling(bool fall) {
  this->falling = fall;
}

void View::Worm::setGrounded(bool grd) {
  this->grounded = grd;
}

void View::Worm::setProtagonic(bool p) {
  this->protagonic = p;
}

void View::Worm::setSightAngle(int angle) {
  this->sight.setAngle(angle);
}