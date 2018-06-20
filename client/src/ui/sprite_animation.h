#ifndef __SPRITE_ANIMATION_H__
#define __SPRITE_ANIMATION_H__

#include "texture.h"

#define DEFAULT_FPC 3

typedef enum {
  INFINITE_GOING_AND_BACK = 0,
  ONLY_GOING = 1,
  INFINITE_GOING = 2,
  DEPENDENT_ON_GRADES = 3
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
      SDL_Rect getNextClipInfiniteGoing(void);
      SDL_Rect getNextClipDependentOnGrades(int grades, int maxGrades = 360);

    public:
      SpriteAnimation(size_t fpc = DEFAULT_FPC, sprite_type_t type = INFINITE_GOING_AND_BACK);
      ~SpriteAnimation();
      void setSpriteSheet(Texture *);

      SDL_Rect getNextClip(int grades = -1, int maxGrades = 360);

      // Verifica si el recorrido del spritesheet
      // finalizo (para ONLY_GOING sprites)
      bool finished(void);

      // Cambia el tipo de sprite sheet
      void changeSpriteType(sprite_type_t);

      // Resetea la animacion y empieza desde el principio
      void reset(void);
  };
}

#endif