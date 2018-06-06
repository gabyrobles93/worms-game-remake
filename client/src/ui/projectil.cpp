#include "projectil.h"

#define ABOUT_TO_EXPLODE 1

View::Projectil::~Projectil(void) {
}

int View::Projectil::getWidth(void) const {
  return this->texture.getWidth();
}

int View::Projectil::getHeight(void) const {
  return this->texture.getWidth();
}

int View::Projectil::getX(void) const {
  return this->x;
}

int View::Projectil::getY(void) const {
  return this->y;
}

void View::Projectil::setX(int x) {
  this->x = x - (this->texture.getWidth() / 2);
}

void View::Projectil::setY(int y) {
  this->y = y - (this->texture.getWidth() / 2);
}

bool View::Projectil::hasExploded(void) const {
  return this->exploded;
}

bool View::Projectil::hasFinished(void) const {
  return this->finished;
}

void View::Projectil::setExplode(bool exploded) {
  this->exploded = exploded;
}

void View::Projectil::setCountdown(int newCount) {
  if (newCount == ABOUT_TO_EXPLODE && this->countdown != newCount) {
    std::cout << "Playing about2explode \n";
    const char * ab2exp[] = {
      gPath.PATH_SOUND_WHAT_THE.c_str(),
      gPath.PATH_SOUND_UH_OH.c_str(),
      gPath.PATH_SOUND_TAKE_COVER.c_str(),
      gPath.PATH_SOUND_RUN_AWAY.c_str()
    };
    this->aboutToExplode.setSound(ab2exp[rand() % 4]);
    this->aboutToExplode.playSound(0);
  }

  this->countdown = newCount;
}

void View::Projectil::setWeaponType(weapon_t type) {
  this->type = type;
}