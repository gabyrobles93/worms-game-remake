#include <SDL2/SDL.h>
#include <string>
#include "worm.h"

#define PADDING 1
#define RECTANGLE_HEIGHT 22
#define DISTANCE_TEXT_FROM_WORM 30
#define FPC 2

View::Worm::Worm(SDL_Renderer * r, std::string name, size_t team, int health) :
  sight(r),
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
  
  this->mirrored = false;
  this->walking = false;
  this->alive = true;
  this->falling = false;
  this->protagonic = false;

  this->x = 0;
  this->y = 0;
  this->inclination = NONE;
  this->angleDirection = 0;

  this->nameText.loadFromRenderedText(r, this->font, name, colors[this->team]);
  this->healthText.loadFromRenderedText(r, this->font, std::to_string(this->health), colors[this->team]);

  this->healthTxt.setTextColor(colors[this->team]);
  this->nameTxt.setTextColor(colors[this->team]);

  this->healthTxt.setText(r, std::to_string(this->health));
  this->nameTxt.setText(r, name);

  this->dataConfiguration = ALL;

  this->states[WS_BREATHING] = new View::Breathing(this, r);
  this->states[WS_WALKING] = new View::Walking(this, r);
  this->states[WS_FALLING] = new View::Falling(this, r);
  this->states[WS_FLYING] = new View::Flying(this, r);
  this->states[WS_DEAD] = new View::Dead(this, r);

  this->state = this->states[WS_BREATHING];
  this->stateName = WS_BREATHING;
}

View::Worm::~Worm() {
  std::map<view_worm_state_t, WormState *>::iterator it = this->states.begin();
  for (; it != this->states.end() ; it++) {
    delete it->second;
  }

  if (this->state) {
    delete this->state;
  }
}

int View::Worm::getWidth(void) const {
  return 60;
}

int View::Worm::getHeight(void) const {
  return 60;
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

void View::Worm::setState(view_worm_state_t newState) {
  this->state->resetAnimation();
  this->stateName = newState;
  this->state = this->states[newState];
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
      this->setState(WS_FLYING);
      return;
    }
  }  

  if (grounded && !walking && !affectedByExplosion) {
    if (this->stateName != WS_BREATHING) {
      this->setState(WS_BREATHING);
      return;
    }
  }

  if (walking && !affectedByExplosion) {
    if (this->stateName != WS_WALKING) {
      this->setState(WS_WALKING);
      return;
    }
  }

  if (falling && !affectedByExplosion) {
    if (this->stateName != WS_FALLING) {
      this->setState(WS_FALLING);
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
      this->setState(WS_DEAD);
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