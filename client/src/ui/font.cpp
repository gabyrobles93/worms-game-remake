#include "font.h"

View::Font::Font(std::string fontPath, size_t fontSize) {
  this->font = TTF_OpenFont(fontPath.c_str(), fontSize);
  if (!this->font) {
    throw View::Exception("%s: %s. %s: %s", ERR_MSG_OPEN_FONT, fontPath.c_str(), "SDL_ttf Error", TTF_GetError());
  }
}

View::Font::~Font() {
  if (this->font) {
    TTF_CloseFont(this->font);
    this->font = NULL;
  }
}

TTF_Font * View::Font::getFont(void) const {
  return this->font;
}
