#include "clock.h"

#define HURRY_TIME 10

View::Clock::Clock(int x, int y, int width, int height) : 
  font(PATH_FONT_ARIAL_BOLD, height - PADDING * 2) {

  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;

  this->hide = false;
}

View::Clock::~Clock(void) {

}

int View::Clock::getWidth(void) const {
	return this->width;
}

int View::Clock::getHeight(void) const {
	return this->height;
}

int View::Clock::getX(void) const {
	return this->x;
}

int View::Clock::getY(void) const {
	return this->y;
}

void View::Clock::setX(int x) {
	this->x = x;
}

void View::Clock::setY(int y) {
	this->y = y;
}

void View::Clock::setTime(int newTime) {
  this->time = newTime;
}

void View::Clock::toggleHide(bool newState) {
  this->hide = newState;
}

void View::Clock::render(SDL_Renderer * r, int x, int y) {
  if (!this->hide) {
    SDL_Color color = {255, 255, 255, 0};

    if (this->time < HURRY_TIME) {
      color = {255, 0, 0, 0};
    }

    this->timeTexture.loadFromRenderedText(r, this->font, std::to_string(this->time), color);
    
    // Black rect
    SDL_Rect blackRect = {
      this->x,
      this->y,
      this->width,
      this->height,
    };
    SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xFF);        
    SDL_RenderFillRect(r, &blackRect);

    // Render time text
    this->timeTexture.render(
      r, 
      this->x + this->width / 2 - this->timeTexture.getWidth() / 2, 
      this->y + this->height / 2 - this->timeTexture.getHeight() / 2
    );
  }
}

