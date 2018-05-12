#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <SDL2/SDL.h>

namespace View {
  class Drawable {
    protected:
    public:
      virtual void render(SDL_Renderer *, int, int) = 0;
      virtual int getWidth(void) = 0;
      virtual int getHeight(void) = 0;
      virtual int getX(void) = 0;
      virtual int getY(void) = 0;
  };
}

#endif