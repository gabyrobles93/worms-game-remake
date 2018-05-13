#ifndef __SPRITE_ANIMATION_H__
#define __SPRITE_ANIMATION_H__

#include "texture.h"

namespace View {
  class SpriteAnimation {
    private:
    public:
      SpriteAnimation(Texture & spriteSheet, std::size_t w, std::size_t h, std::size_t qty);
      ~SpriteAnimation();
  };
}

#endif