#ifndef __VIEW_WORM_H__
#define __VIEW_WORM_H__

#include <SDL2/SDL.h>
#include <map>
#include "texture.h"
#include "drawable.h"
#include "sprite_animation.h"

typedef enum {
  BREATH_1,
  BREATH_1_UP,
  BREATH_1_DOWN,

  WALK,
  WALK_UP,
  WALK_DOWN,
} worm_animation_t;

namespace View {
  class Worm: public Drawable {
    private:
      View::SpriteAnimation currentSprite;
      worm_animation_t currentAnimation;
      Texture currentTexture;

      std::map<worm_animation_t, Texture> textures;

    public:
      Worm(SDL_Renderer *);
      ~Worm();
      void handleEvent(SDL_Event &);
      virtual int getWidth(void);
      virtual int getHeight(void);
      virtual int getX(void);
      virtual int getY(void);
      virtual void render(SDL_Renderer *, int, int);
  };
}

#endif