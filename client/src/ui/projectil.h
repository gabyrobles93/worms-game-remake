#ifndef __PROJECTIL_H__
#define __PROJECTIL_H__

#include <SDL2/SDL.h>
#include "drawable.h"
#include "sound_effect.h"
#include "sprite_animation.h"
#include "texture.h"

namespace View {
  class Projectil: public Drawable {
    protected:
      Texture texture;
      SoundEffect sound;

      bool exploded;
      bool finished;
      int countdown;
      int retioExplosion;

    public:
      virtual ~Projectil();
      virtual int getWidth(void) const;
      virtual int getHeight(void) const;
      virtual int getX(void) const;
      virtual int getY(void) const;
      virtual void setX(int);
      virtual void setY(int);
      virtual void render(SDL_Renderer *, int, int) = 0;

      bool hasExploded(void) const;
      bool hasFinished(void) const;
      void setCountdown(int);
      void setExplode(bool);
  };
}

#endif