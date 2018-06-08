#include "shoot_power.h"

#define WHITE_TICKNESS 3


View::ShootPower::ShootPower(int w, int h, int maxTime) {
  this->width = w;
  this->height = h;
  this->maxTimeShoot = maxTime;
  this->x = 0;
  this->y = 0;
}

View::ShootPower::~ShootPower() {

}

int View::ShootPower::getWidth(void) const {
  return this->width;
}

int View::ShootPower::getHeight(void) const {
  return this->height;
}

int View::ShootPower::getX(void) const {
  return this->x;
}

int View::ShootPower::getY(void) const {
  return this->y;
}

void View::ShootPower::setX(int x) {
  this->x = x - this->width / 2;
}

void View::ShootPower::setY(int y) {
  this->y = y - this->height / 2;
}

void View::ShootPower::render(SDL_Renderer * r, int camX, int camY) {
  return;
}

void View::ShootPower::render(SDL_Renderer * r, int timeShooting) {
  // White rect
  SDL_Rect whiteRect = {
    this->x,
    this->y,
    this->width,
    this->height,
  };

  SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);        
  SDL_RenderFillRect(r, &whiteRect);

  int totalWidth = this->width - 2 * WHITE_TICKNESS;
  // Black rect
  SDL_Rect blackRect = {
    this->x + WHITE_TICKNESS,
    this->y + WHITE_TICKNESS,
    totalWidth,
    this->height - 2 * WHITE_TICKNESS,
  };
  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xFF);        
  SDL_RenderFillRect(r, &blackRect);

  float factor = ((float)timeShooting / (float)this->maxTimeShoot);
  int widthRedRect = (int)(factor * totalWidth);
  // Red rect
  SDL_Rect redRect = {
    this->x + WHITE_TICKNESS,
    this->y + WHITE_TICKNESS,
    widthRedRect,
    this->height - 2 * WHITE_TICKNESS,
  };

  SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0x00, 0xFF);        
  SDL_RenderFillRect(r, &redRect);
}