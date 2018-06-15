#ifndef __WALKING_H__
#define __WALKING_H__

#include <map>
#include "sprite_animation.h"
#include "texture.h"
#include "worm_state.h"
#include "worm.h"
#include "types.h"

namespace View {
  class Worm;

  class Walking: public WormState {
    private:
      std::map<worm_inclination_t, View::Texture> textures;
      std::map<worm_inclination_t, View::SpriteAnimation> sprites;

    public:
      Walking(View::Worm * context, SDL_Renderer * r);
      ~Walking();
      virtual void render(SDL_Renderer *, int, int, worm_inclination_t, bool);
  };
}


#endif