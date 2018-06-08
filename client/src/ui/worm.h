#ifndef __VIEW_WORM_H__
#define __VIEW_WORM_H__

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include "texture.h"
#include "drawable.h"
#include "paths.h"
#include "sprite_animation.h"
#include "sound_effect.h"
#include "font.h"
#include "sight.h"

typedef enum {
  PLAIN_WORM,

  BREATH_1,
  BREATH_1_UP,
  BREATH_1_DOWN,

  WALK,
  WALK_UP,
  WALK_DOWN,

  ROLL,

  FALLDN
} worm_animation_t;

namespace View {
  class Worm: public Drawable {
    private:
      // Animation
      View::SpriteAnimation sprite;
      worm_animation_t currentAnimation;
      std::map<worm_animation_t, Texture> textures;
      
      // Animation state
      bool grounded;
      bool mirrored;
      bool walking;
      bool falling;
      bool alive;
      bool protagonic;

      Sight sight;


      // Worm data
      std::string name;
      size_t team;
      int health;

      // Sound
      SoundEffect walkingSound;

      // Worm data UI
      Font font;
      Texture nameText;
      Texture healthText;

    public:
      Worm(SDL_Renderer *, std::string, size_t, int);
      virtual ~Worm(void);
      virtual int getWidth(void) const;
      virtual int getHeight(void) const;
      virtual int getX(void) const;
      virtual int getY(void) const;
      virtual void setX(int);
      virtual void setY(int);
      virtual void render(SDL_Renderer *, int, int);
      void setProtagonic(bool);
      void setMirrored(bool);
      void setWalking(bool);
      void renderWormData(SDL_Renderer *, int, int);
      void setHealth(int);
      void setFalling(bool);
      void setGrounded(bool);
      void setSightAngle(int);
      int getHealth(void);
      bool isAlive(void);
  };
}

#endif
