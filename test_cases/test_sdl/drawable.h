#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <SDL2/SDL.h>

namespace View {
  class Drawable {
    protected:
    public:
      virtual void render(SDL_Renderer *, int, int) = 0;
  };
}

#endif