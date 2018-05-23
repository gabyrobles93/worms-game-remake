#ifndef __SPRITE_ANIMATION_H__
#define __SPRITE_ANIMATION_H__

#include "texture.h"

namespace View {
  class SpriteAnimation {
    private:
      Texture * currentSpriteSheet;
      
      int fpc; // Frames per clip
      int counter;
      int clipWidth;
      int clipHeight;
      int numClips;
      bool reverse;

    public:
      SpriteAnimation(size_t);
      ~SpriteAnimation();
      void setSpriteSheet(Texture *);

      SDL_Rect getNextClip(void);
  };
}

#endif