#ifndef __SPRITE_ANIMATION_H__
#define __SPRITE_ANIMATION_H__

#include "texture.h"
#include "thread.h"

namespace View {
  class SpriteAnimation: public Thread {
    private:
      bool running;
      Texture * currentSpriteSheet;
      SDL_Renderer * renderer;

    public:
      SpriteAnimation(SDL_Renderer *);
      ~SpriteAnimation();
      void setSpriteSheet(Texture *);
      void stopAnimation(void);

      virtual void run(void);
      virtual bool isRunning(void) const;
  };
}

#endif