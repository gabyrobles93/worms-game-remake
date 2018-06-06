#ifndef __GREEN_GRENADE_H__
#define __GREEN_GRENADE_H__

#include <SDL2/SDL.h>
#include "explosion.h"
#include "paths.h"
#include "projectil.h"
#include "rectangle_text.h"


namespace View {
  class GreenGrenade: public Projectil {
    private:
      SpriteAnimation sprite;
      Explosion explosion;
      RectangleText countdownText;

    public:
      GreenGrenade(SDL_Renderer * r, int countdown, int ratioExplosion = 100);
      ~GreenGrenade();

      virtual void render(SDL_Renderer * r, int, int);
  };
}

#endif