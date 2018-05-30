#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <SDL2/SDL.h>
#include "drawable.h"
#include "font.h"
#include "resources_paths.h"
#include "texture.h"

#define TEXT_SIZE 40
#define PADDING 5

namespace View {
  class Clock: public Drawable {
    private:
      Font font;
      int time;
      Texture timeTexture;

    public:
      Clock(int x, int y, int width, int height);
      ~Clock();
      void setTime(int);

      virtual void render(SDL_Renderer *, int, int);
      virtual int getWidth(void) const;
      virtual int getHeight(void) const;
      virtual int getX(void) const;
      virtual int getY(void) const;
      virtual void setX(int);
      virtual void setY(int);
  };
}

#endif