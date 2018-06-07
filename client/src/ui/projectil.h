#ifndef __PROJECTIL_H__
#define __PROJECTIL_H__

#include <SDL2/SDL.h>
#include "drawable.h"
#include "paths.h"
#include "sound_effect.h"
#include "sprite_animation.h"
#include "texture.h"
#include "types.h"

#define COUNTDOWN_TEXT_SIZE 18

namespace View {
  class Projectil: public Drawable {
    protected:
      Texture texture;
      SoundEffect sound;
      SoundEffect aboutToExplode;
      bool playedAboutToExplode;

      bool exploded;
      bool finished;
      int countdown;
      int ratioExplosion;
      weapon_t type;

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
      void setWeaponType(weapon_t);
  };
}

#endif