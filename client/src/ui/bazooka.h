#ifndef __BAZOOKA_H__
#define __BAZOOKA_H__

#include "explosion.h"
#include "rectangle_text.h"
#include "projectil.h"

namespace View {
  class Bazooka: public Projectil {
    private:
      SpriteAnimation sprite;
      Explosion explosion;

    public:
      Bazooka(SDL_Renderer * r, int ratioExplosion = 100);
      ~Bazooka();
      virtual void render(SDL_Renderer * r, int, int);
  };
}

#endif