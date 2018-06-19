#ifndef __PICK_WEAPON_H__
#define __PICK_WEAPON_H__

#include <map>
#include "sprite_animation.h"
#include "texture.h"
#include "worm_state.h"
#include "worm.h"
#include "types.h"
#include "sound_effect.h"

namespace View {
  class Worm;

  class PickWeapon: public WormState {
    private:
      std::map<weapon_t, std::map<worm_inclination_t, Texture>> textures;
      std::map<weapon_t, std::map<worm_inclination_t, SpriteAnimation>> sprites;

    public:
      PickWeapon(View::Worm * context, SDL_Renderer * r);
      ~PickWeapon();
      virtual void render(SDL_Renderer *, int, int, worm_inclination_t, bool, int);
  };
}


#endif