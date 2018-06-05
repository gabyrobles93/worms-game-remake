#ifndef __SIGHT_H__
#define __SIGHT_H__

#include "drawable.h"
#include "texture.h"
#include "paths.h"
#include "sprite_animation.h"

#define DEGTORAD 0.0174533

namespace View {
  class Sight: public Drawable {
    private:
      Texture texture;
      SpriteAnimation sprite;
      int ratio;
      float angle;

      int xCenter;
      int yCenter;

      bool mirrored;

    public:
      Sight(SDL_Renderer * r, int ratio = 100, int angle = 0);
      ~Sight();

      void setXYcenter(int, int);
      void setAngle(int);
      void setRatio(int);
      void setMirrored(bool);
      
      virtual int getWidth(void) const;
      virtual int getHeight(void) const;
      virtual int getX(void) const;
      virtual int getY(void) const;
      virtual void setX(int);
      virtual void setY(int);
      virtual void render(SDL_Renderer *, int, int);
  };
}

#endif