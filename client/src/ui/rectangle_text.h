#ifndef __RECTANGLE_TEXT_H__
#define __RECTANGLE_TEXT_H__

#include "drawable.h"

namespace View {
  class RectangleText: public Drawable {
    private:
      Texture text;
    public:
      virtual int getWidth(void) const;
      virtual int getHeight(void) const;
      virtual int getX(void) const;
      virtual int getY(void) const;
      virtual void setX(int);
      virtual void setY(int);
      virtual void render(SDL_Renderer *, int, int) = 0;
  };
}

#endif