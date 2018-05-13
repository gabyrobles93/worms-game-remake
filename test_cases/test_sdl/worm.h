#ifndef __VIEW_WORM_H__
#define __VIEW_WORM_H__

#include <SDL2/SDL.h>
#include "texture.h"
#include "drawable.h"

namespace View {
  class Worm: public Drawable {
    private:
      Texture currentTexture;

    public:
      virtual int getWidth(void);
      virtual int getHeight(void);
      virtual int getX(void);
      virtual int getY(void);
      virtual void render(SDL_Renderer *, int, int);
  };
}

#endif
