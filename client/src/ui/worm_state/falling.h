#ifndef __FALLING_H__
#define __FALLING_H__

#include <map>
#include "sprite_animation.h"
#include "texture.h"
#include "worm_state.h"
#include "worm.h"
#include "types.h"

namespace View {
  class Worm;

  class Falling: public WormState {
    private:
      Texture texture;
      SpriteAnimation sprite;

    public:
      Falling(View::Worm * context, SDL_Renderer * r);
      ~Falling();
      virtual void render(SDL_Renderer *, int, int, worm_inclination_t, bool, int);
  };
}


#endif