#include "rectangle_text.h"

View::RectangleText::RectangleText(int height, int padding, std::string fontPath) :
  font(fontPath, height - padding * 2) {

  this->x = 0;
  this->y = 0;
  this->width = 0; // El ancho dependera del texto
  this->height = height; // El alto del rectangulo es configurable

  // Text color default blanco
  this->textColor = {255, 255, 255, 0};

  // Background color default negro
  this->backgroundColor = {0, 0, 255, 0};

  this->hide = false;
  this->padding = padding;
}

View::RectangleText::~RectangleText() {

}

int View::RectangleText::getWidth(void) const {
	return this->width;
}

int View::RectangleText::getHeight(void) const {
	return this->height;
}

int View::RectangleText::getX(void) const {
	return this->x;
}

int View::RectangleText::getY(void) const {
	return this->y;
}

void View::RectangleText::setX(int x) {
	this->x = x - this->width / 2;
}

void View::RectangleText::setY(int y) {
	this->y = y - this->height / 2;
}

void View::RectangleText::setText(SDL_Renderer * r, const std::string & text) {
  this->text.loadFromRenderedText(r, this->font, text, this->textColor);
  this->width = this->text.getWidth() + this->padding * 2;
}

void View::RectangleText::setTextColor(SDL_Color & c) {
  this->textColor = c;
}

void View::RectangleText::setBackgroundColor(SDL_Color & c) {
  this->backgroundColor = c;
}

void View::RectangleText::toggleHide(bool h) {
  this->hide = h;
}

void View::RectangleText::render(SDL_Renderer * r, int camX, int camY) {
  if (!this->hide) {    
    // Background rect
    SDL_Rect bgRect = {
      this->x - this->width / 2 - camX,
      this->y - this->height / 2 - camY,
      this->width,
      this->height,
    };
    SDL_SetRenderDrawColor(
      r, 
      this->backgroundColor.r, 
      this->backgroundColor.g, 
      this->backgroundColor.b, 
      this->backgroundColor.a
    );   

    SDL_RenderFillRect(r, &bgRect);

    // Render text
    this->text.render(
      r, 
      this->x - this->width / 2 + this->padding - camX, 
      this->y - this->height / 2 + this->padding - camY
    );
  }
}
