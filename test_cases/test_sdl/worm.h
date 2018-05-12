#ifndef __VIEW_WORM_H__
#define __VIEW_WORM_H__

#include <SDL2/SDL.h>
#include "drawable.h"

namespace View {
  class Worm: public Drawable {
    private:
    public:
      virtual void render(SDL_Renderer *, int, int);
  };
}

#endif
