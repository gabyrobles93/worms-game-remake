#ifndef __DYNAMITE_H__
#define __DYNAMITE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "drawable.h"
#include "paths.h"
#include "projectil.h"
#include "sprite_animation.h"
#include "sound_effect.h"
#include "texture.h"


namespace View {
  class Dynamite: public Projectil {
    private:
      SpriteAnimation sprite;

    public:
      Dynamite(SDL_Renderer *, int);
      ~Dynamite();

      virtual void render(SDL_Renderer *, int, int);
  };
}

#endif