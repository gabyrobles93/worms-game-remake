#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include <SDL2/SDL.h>
#include "drawable.h"
#include "paths.h"
#include "sprite_animation.h"
#include "sound_effect.h"
#include "texture.h"

#define EXPLOSION_FPC 3

namespace View {
  class Explosion: public Drawable {
    private:
      Texture texture;
      SpriteAnimation sprite;
      SoundEffect sound;
    public:
      Explosion(SDL_Renderer * r, int ratio, std::string weapon = "Bazooka");
      ~Explosion();

      bool finishedExplosion(void);

      virtual void render(SDL_Renderer *, int, int);
      virtual int getWidth(void) const;
      virtual int getHeight(void) const;
      virtual int getX(void) const;
      virtual int getY(void) const;
      virtual void setX(int);
      virtual void setY(int);
  };
}

#endif