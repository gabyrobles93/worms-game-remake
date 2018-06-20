#ifndef __DEAD_H__
#define __DEAD_H__

#include <map>
#include "worm_state.h"
#include "sprite_animation.h"
#include "sound_effect.h"
#include "texture.h"
#include "worm.h"
#include "types.h"
#include "explosion.h"

namespace View {
  class Worm;
  
  class Dead: public WormState {
    private:
      Texture textureDying;
      SpriteAnimation spriteDying;
      Explosion explosion;
      
      Texture textureGrave;
      SpriteAnimation spriteGrave;

      SoundEffect sound;

      bool dying;

    public:
      Dead(View::Worm * context, SDL_Renderer * r);
      ~Dead();
      virtual void render(SDL_Renderer *, int, int, worm_inclination_t, bool, int angle);
      virtual void resetAnimation(void);
  };
}


#endif