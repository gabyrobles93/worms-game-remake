#ifndef __SPRITE_ANIMATION_H__
#define __SPRITE_ANIMATION_H__

#include "texture.h"

typedef enum {
  INFINITE_GOING_AND_BACK = 0,
  ONLY_GOING = 1
} sprite_type_t;

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
      bool finish;

      sprite_type_t type;

      SDL_Rect getNextClipInfiniteRoundTrip(void);
      SDL_Rect getNextClipOnlyGoing(void);

    public:
      SpriteAnimation(size_t, sprite_type_t type = INFINITE_GOING_AND_BACK);
      ~SpriteAnimation();
      void setSpriteSheet(Texture *);

      SDL_Rect getNextClip(void);

      // Verifica si el recorrido del spritesheet
      // finalizo (para ONLY_GOING sprites)
      bool finished(void);
  };
}

#endif