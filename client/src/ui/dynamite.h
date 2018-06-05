#ifndef __DYNAMITE_H__
#define __DYNAMITE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include "drawable.h"
#include "explosion.h"
#include "paths.h"
#include "projectil.h"
#include "rectangle_text.h"
#include "sprite_animation.h"
#include "sound_effect.h"
#include "texture.h"


namespace View {
  class Dynamite: public Projectil {
    private:
      SpriteAnimation sprite;
      Explosion explosion;
      RectangleText countdownText;

    public:
      Dynamite(SDL_Renderer *, int c, int ratio = 100);
      ~Dynamite();

      virtual void render(SDL_Renderer * r, int, int);
  };
}

#endif