#ifndef __WIND_H__
#define __WIND_H__

#include <stdlib.h>
#include "drawable.h"
#include "rectangle_text.h"
#include "paths.h"

namespace View {
  class Wind: public Drawable {
    private:
      int windPower;
      int whiteTickness;
      int windRectWidth;
      int windRectX;
      int windRectY;

      RectangleText text;

    public:
      Wind(SDL_Renderer * r, int, int);
      ~Wind();

      virtual int getWidth(void) const;
      virtual int getHeight(void) const;
      virtual int getX(void) const;
      virtual int getY(void) const;
      virtual void setX(int);
      virtual void setY(int);
      virtual void render(SDL_Renderer *, int, int);

      void setWindPower(int);
  };
}

#endif