#ifndef __FLYING_H__
#define __FLYING_H__

#include <map>
#include "sprite_animation.h"
#include "texture.h"
#include "worm_state.h"
#include "worm.h"
#include "types.h"
#include "sound_effect.h"

namespace View {
  class Worm;

  class Flying: public WormState {
    private:
      std::map<size_t, Texture> textures;
      std::map<size_t, SpriteAnimation> sprites;
      size_t index;
      SoundEffect sound;

    public:
      Flying(View::Worm * context, SDL_Renderer * r);
      ~Flying();
      virtual void render(SDL_Renderer *, int, int, worm_inclination_t, bool, int);
  };
}


#endif