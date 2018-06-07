#ifndef __HOLY_GRENADE_H__
#define __HOLY_GRENADE_H__

#include <SDL2/SDL.h>
#include "explosion.h"
#include "paths.h"
#include "projectil.h"
#include "sound_effect.h"
#include "rectangle_text.h"


namespace View {
  class HolyGrenade: public Projectil {
    private:
      SpriteAnimation sprite;
      Explosion explosion;
      RectangleText countdownText;
      SoundEffect holySound;
      bool holySoundPlayed;

    public:
      HolyGrenade(SDL_Renderer * r, int countdown, int ratioExplosion = 100);
      ~HolyGrenade();

      virtual void render(SDL_Renderer * r, int, int);
  };
}

#endif