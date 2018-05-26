#ifndef __VIEW_WORM_H__
#define __VIEW_WORM_H__

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include "texture.h"
#include "drawable.h"
#include "resources_paths.h"
#include "sprite_animation.h"

#include "font.h"

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
      // Animation
      View::SpriteAnimation sprite;
      worm_animation_t currentAnimation;
      std::map<worm_animation_t, Texture> textures;
      
      // Animation state
      bool mirrored;
      bool walking;
      bool alive;

      // Worm data
      std::string name;
      size_t team;
      int health;

      // Worm data UI
      Font font;
      Texture nameText;
      Texture healthText;

    public:
      Worm(SDL_Renderer *, std::string, size_t, int);
      virtual ~Worm(void);
      /* void handleEvent(SDL_Event &); */
      virtual int getWidth(void) const;
      virtual int getHeight(void) const;
      virtual int getX(void) const;
      virtual int getY(void) const;
      virtual void setX(int);
      virtual void setY(int);
      void setMirrored(bool);
      void setWalking(bool);
      virtual void render(SDL_Renderer *, int, int);
      void renderWormData(SDL_Renderer *, int, int);
      void setHealth(int);
      int getHealth(void);
      bool isAlive(void);
  };
}

#endif
