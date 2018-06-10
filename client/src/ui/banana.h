#ifndef __BANANA_H__
#define __BANANA_H__

#include "explosion.h"
#include "rectangle_text.h"
#include "projectil.h"

namespace View {
  class Banana: public Projectil {
    private:
      SpriteAnimation sprite;
      Explosion explosion;
      RectangleText countdownText;
    public:
      Banana(SDL_Renderer * r, int countdown, int ratioExplosion = 100);
      ~Banana();
      virtual void render(SDL_Renderer * r, int, int);
  };
}

#endif