#include <SDL2/SDL.h>
#include <string>
#include "worm.h"

#define PADDING 1
#define RECTANGLE_HEIGHT 22
#define DISTANCE_TEXT_FROM_WORM 30
#define FPC 2

View::Worm::Worm(SDL_Renderer * r, std::string name, size_t team, int health) :
  renderer(r),
  sprite(FPC),
  sight(r),
  name(name),
  team(team),
  health(health),
  font(gPath.PATH_FONT_ARIAL_BOLD, 20),
  healthTxt(RECTANGLE_HEIGHT, PADDING, gPath.PATH_FONT_ARIAL_BOLD),
  nameTxt(RECTANGLE_HEIGHT, PADDING, gPath.PATH_FONT_ARIAL_BOLD) {

  SDL_Color colors[] = {
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
  this->inclination = NONE;
  this->angleDirection = 0;

  this->walkingSound.setSound(gPath.PATH_SOUND_WORM_WALKING);

  this->nameText.loadFromRenderedText(r, this->font, this->name, colors[this->team]);
  this->healthText.loadFromRenderedText(r, this->font, std::to_string(this->health), colors[this->team]);

  this->healthTxt.setTextColor(colors[this->team]);
  this->nameTxt.setTextColor(colors[this->team]);

  this->healthTxt.setText(r, std::to_string(this->health));
  this->nameTxt.setText(r, this->name);

  this->dataConfiguration = ALL;

  this->state = new View::Breathing(this, this->renderer);
  this->stateName = WS_BREATHING;
}

View::Worm::~Worm() {
  if (this->state) {
    delete this->state;
  }
}

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
  this->healthTxt.setX(x);
  this->nameTxt.setX(x);
  this->x = x;
}

void View::Worm::setY(int y) {
  this->healthTxt.setY(y - this->healthTxt.getHeight() / 2 - DISTANCE_TEXT_FROM_WORM);
  this->nameTxt.setY(this->healthTxt.getY() - this->nameTxt.getHeight() / 2);
  this->y = y;
}

void View::Worm::setState(WormState * newState) {
  delete this->state;
  this->state = newState;
}

void View::Worm::updateState(const YAML::Node & status) {
  if (this->stateName == WS_DEAD) {
    return;
  }

  // std::cout << status << std::endl << std::endl;
  this->mirrored = status["mirrored"].as<int>();
  this->inclination = (worm_inclination_t)status["inclination"].as<int>();
  bool walking = status["walking"].as<int>();
  bool falling = status["falling"].as<int>();
  bool grounded = status["grounded"].as<int>();
  this->affectedByExplosion = status["affected_by_explosion"].as<int>();
  this->angleDirection = status["angle_direction"].as<int>();

  if (affectedByExplosion) {
    if (this->stateName != WS_FLYING) {
      this->stateName = WS_FLYING;
      this->setState(new View::Flying(this, this->renderer));
      return;
    }
  }  

  if (grounded && !walking && !affectedByExplosion) {
    if (this->stateName != WS_BREATHING) {
      this->stateName = WS_BREATHING;
      this->setState(new View::Breathing(this, this->renderer));
      return;
    }
  }

  if (walking && !affectedByExplosion) {
    if (this->stateName != WS_WALKING) {
      this->stateName = WS_WALKING;
      this->setState(new View::Walking(this, this->renderer));
      return;
    }
  }

  if (falling && !affectedByExplosion) {
    if (this->stateName != WS_FALLING) {
      this->stateName = WS_FALLING;
      this->setState(new View::Falling(this, this->renderer));
      return;
    }
  }
}

void View::Worm::render(SDL_Renderer * r, int camX, int camY) {
  this->state->render(r, camX, camY, this->inclination, this->mirrored, this->angleDirection);
  
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
  if (this->stateName == WS_DEAD) {
    return;
  }
  
  if (this->dataConfiguration != NO_DATA) {
    this->healthTxt.setText(r, std::to_string(this->health));
    this->healthTxt.render(r, camX, camY);

    if (this->dataConfiguration == ALL) {
      this->nameTxt.render(r, camX, camY);
    }  
  }
}

void View::Worm::setHealth(int newHealth) {
  if (this->stateName != WS_DEAD) {
    this->health = newHealth;
    if (this->health <= 0) {
      this->stateName = WS_DEAD;
      this->affectedByExplosion = false;
      this->setState(new View::Dead(this, this->renderer));
    }
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

void View::Worm::setAffectedByExplosion(bool af) {
  this->affectedByExplosion = af;
}

void View::Worm::setDataConfiguration(worm_data_cfg_t config) {
  this->dataConfiguration = config;
}

bool View::Worm::isAffectedByExplosion() {
  return this->affectedByExplosion;
}

std::string View::Worm::getName() const {
  return this->name;
}