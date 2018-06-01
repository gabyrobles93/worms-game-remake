#ifndef __DYNAMITE_H__
#define __DYNAMITE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "drawable.h"
#include "paths.h"
#include "sprite_animation.h"
#include "sound_effect.h"
#include "texture.h"


namespace View {
  class Dynamite: public Drawable {
    private:
      Texture texture;
      SpriteAnimation sprite;
      SoundEffect sound;

      bool hasExploded;
      
    public:
      Dynamite(SDL_Renderer *);
      ~Dynamite();

      bool exploded(void);

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