#ifndef __AIR_STRIKE_H__
#define __AIR_STRIKE_H__

#include "explosion.h"
#include "rectangle_text.h"
#include "projectil.h"

namespace View {
  class AirStrike: public Projectil {
    private:
      SpriteAnimation sprite;
      Explosion explosion;

    public:
      AirStrike(SDL_Renderer * r, int ratioExplosion = 100);
      ~AirStrike();
      virtual void render(SDL_Renderer * r, int, int);
  };
}

#endif