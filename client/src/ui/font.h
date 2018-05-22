#ifndef __FONT_H__
#define __FONT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "view_exceptions.h"
#include "view_exceptions_messages.h"

namespace View {
  class Font {
    private:
      TTF_Font * font;
    public:
      Font(std::string, size_t);
      ~Font();
      TTF_Font * getFont(void) const;
  };
}

#endif