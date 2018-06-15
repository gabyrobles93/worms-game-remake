#ifndef __BREATHING_H__
#define __BREATHING_H__

#include <map>
#include "worm_state.h"
#include "sprite_animation.h"
#include "texture.h"
#include "worm.h"
#include "types.h"

namespace View {
  class Worm;
  
  class Breathing: public WormState {
    private:
      std::map<worm_inclination_t, View::Texture> textures;
      std::map<worm_inclination_t, View::SpriteAnimation> sprites;

    public:
      Breathing(View::Worm * context, SDL_Renderer * r);
      ~Breathing();
      virtual void render(SDL_Renderer *, int, int, worm_inclination_t, bool);
  };
}


#endif