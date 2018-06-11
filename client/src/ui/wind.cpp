#include "wind.h"

#define MAX_MOD_WIND_POWER 6
#define WHITE_TICKNESS_PERCENT 10

View::Wind::Wind(SDL_Renderer * r, int width, int height) : 
  text(height / 2, 2, gPath.PATH_FONT_ARIAL_BOLD) {
  this->windPower = 0;
  this->width = width;
  this->height = height;
  this->x = 0;
  this->y = 0;

  this->whiteTickness = this->height / (100 / WHITE_TICKNESS_PERCENT);

  SDL_Color black = {0,0,0,0};
  this->text.setBackgroundColor(black);

  SDL_Color white = {255, 255, 255, 255};
  this->text.setTextColor(white);

  this->text.setText(r, "Wind force");
}

View::Wind::~Wind() {

}

int View::Wind::getWidth(void) const {
	return this->width;
}

int View::Wind::getHeight(void) const {
	return this->height;
}

int View::Wind::getX(void) const {
	return this->x;
}

int View::Wind::getY(void) const {
	return this->y;
}

void View::Wind::setX(int x) {
	this->x = x - this->width / 2;
  this->text.setX(x - this->text.getWidth() * 2 - this->whiteTickness);
}

void View::Wind::setY(int y) {
	this->y = y - this->height / 2;
  this->text.setY(y + this->text.getHeight() / 2);
}

void View::Wind::render(SDL_Renderer * r, int camX, int camY) {
  // White rect
  SDL_Rect whiteRect = {
    this->x,
    this->y,
    this->width,
    this->height,
  };

  SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);        
  SDL_RenderFillRect(r, &whiteRect);

  // Black rects
  SDL_Rect blackRect = {
    this->x + this->whiteTickness,
    this->y + this->whiteTickness,
    this->width - this->whiteTickness - this->width / 2 - this->whiteTickness / 2, 
    this->height - this->whiteTickness * 2,
  };

  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xFF);        
  SDL_RenderFillRect(r, &blackRect);

  blackRect = {
    this->x + this->width / 2 + this->whiteTickness / 2,
    this->y + this->whiteTickness,
    this->width - this->whiteTickness - this->width / 2 - this->whiteTickness / 2, 
    this->height - this->whiteTickness * 2,
  };

  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xFF);        
  SDL_RenderFillRect(r, &blackRect);

  SDL_Rect windRect = {
    this->windRectX,
    this->windRectY,
    this->windRectWidth, 
    this->height - this->whiteTickness * 2,
  };

  if (this->windPower > 0) {
    SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0x00, 0xFF);
  } else {
    SDL_SetRenderDrawColor(r, 0x00, 0x00, 0xFF, 0xFF);
  }
      
  SDL_RenderFillRect(r, &windRect);

  this->text.render(r, 0, 0);
}

void View::Wind::setWindPower(int newPower) {
  this->windPower = newPower;

  int maxWidth = this->width / 2 - this->whiteTickness - this->whiteTickness / 2;
  this->windRectWidth = (abs(newPower) * maxWidth) / MAX_MOD_WIND_POWER;

  if (newPower > 0) {
    this->windRectX = this->x + this->width / 2 + this->whiteTickness / 2;
  }

  if (newPower <= 0) {
    this->windRectX = this->x + this->width / 2 - this->whiteTickness / 2 - this->windRectWidth;
  }

  this->windRectY = this->y + this->whiteTickness;
}
