#include "camera.h"

View::Camera::Camera(int camW, int camH, int levelW, int levelH) :
  width(camW), height(camH), levelWidth(levelW), levelHeight(levelH) {
    // Inicializamos la camara centrada al nivel
    this->camera = {
      (this->levelWidth - this->width) / 2,
      (this->levelHeight - this->height) / 2,
      this->width,
      this->height
    };
}

View::Camera::~Camera() {}

int View::Camera::getX(void) const {
  return this->camera.x;
}

int View::Camera::getY(void) const {
  return this->camera.y;
}

SDL_Rect View::Camera::getCamera(void) const {
  return this->camera;
}

void View::Camera::setX(int x) {
  if (x < 0) {
    this->camera.x = 0;
    return;
  }

  if (x > this->levelWidth - this->width) {
    this->camera.x = this->levelWidth - this->width;
    return;
  }

  this->camera.x = x;
}

void View::Camera::setY(int y) {
  if (y < 0) {
    this->camera.y = 0;
    return;
  }

  if (y > this->levelHeight - this->height) {
    this->camera.y = this->levelHeight - this->height;
    return;
  }
  
  this->camera.y = y;
}

void View::Camera::setXY(int x, int y) {
  this->setX(x);
  this->setY(y);
  return;
}

void View::Camera::focus(Drawable & d) {
  this->setX(d.getX() - this->width / 2);
  this->setY(d.getY() - this->height / 2);
}

void View::Camera::handleEvent(SDL_Event & e) {
  if (e.key.keysym.sym == SDLK_a) {
    this->setX(this->camera.x - 100);
  }
  if (e.key.keysym.sym == SDLK_d) {
    this->setX(this->camera.x + 100);
  }
  if (e.key.keysym.sym == SDLK_w) {
    this->setY(this->camera.y - 100);
  }
  if (e.key.keysym.sym == SDLK_s) {
    this->setY(this->camera.y + 100);
  }
}