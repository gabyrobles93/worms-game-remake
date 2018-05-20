#ifndef __VIEW_WORM_H__
#define __VIEW_WORM_H__

#include <SDL2/SDL.h>
#include <map>
#include "texture.h"
#include "drawable.h"
#include "resources_paths.h"
#include "sprite_animation.h"

typedef enum {
  PLAIN_WORM,

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
      bool mirrored;
      std::string name;
      std::string team;
      int health;

    public:
      Worm(SDL_Renderer *, std::string&, std::string &, int);
      ~Worm();
      /* void handleEvent(SDL_Event &); */
      virtual int getWidth(void) const;
      virtual int getHeight(void) const;
      virtual int getX(void) const;
      virtual int getY(void) const;
      virtual void setX(int);
      virtual void setY(int);
      virtual void render(SDL_Renderer *, int, int);
      void setHealth(int);
      int getHealth(void);
  };
}

#endif
