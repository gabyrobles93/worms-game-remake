#include "flash_notice.h"

#define FLASH_NOTICE_PADDING 5
#define MAX_TIME_DISPLAYING 1500

FlashNotice::FlashNotice(void) : 
  notice(30) {
}

FlashNotice::FlashNotice(int sw, int sh, int percentWindow) :
  notice(sh / (100 / percentWindow)) {
  this->screenWidth = sw;
  this->screenHeight = sh;
}

FlashNotice::~FlashNotice() {

}

void FlashNotice::showFlashNotice(SDL_Renderer * r, const std::string & notice) {
  SDL_Color black = {0,0,0,0};
  SDL_Color white = {255,255,255,255};
  this->notice.setBackgroundColor(black);
  this->notice.setTextColor(white);
  this->notice.setText(r, notice);
  if (this->timer.isStarted()) {
    this->timer.stop();
  }
  this->timer.start();
  this->notice.setX(this->screenWidth / 2);
  this->notice.setY(FLASH_NOTICE_PADDING + this->notice.getHeight() / 2);
}

void FlashNotice::showFlashError(SDL_Renderer * r, const std::string & notice) {
  SDL_Color black = {0,0,0,0};
  SDL_Color red = {255,0,0,0};
  this->notice.setBackgroundColor(black);
  this->notice.setTextColor(red);
  this->notice.setText(r, notice);
  if (this->timer.isStarted()) {
    this->timer.stop();
  }
  this->timer.start();
  this->notice.setX(this->screenWidth / 2);
  this->notice.setY(FLASH_NOTICE_PADDING + this->notice.getHeight() / 2);
}

void FlashNotice::render(SDL_Renderer * r) {
  if (this->timer.getTicks() < MAX_TIME_DISPLAYING && this->timer.isStarted()) {
    this->notice.render(r, 0, 0);
  } else {
    if (this->timer.isStarted()) {
      this->timer.stop();
    }
  }
}

void FlashNotice::setScreenWidth(int w) {
  this->screenWidth = w;
}

void FlashNotice::setScreenHeight(int h) {
  this->screenHeight = h;
}

