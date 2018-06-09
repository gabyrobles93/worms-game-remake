#ifndef __SHOOT_POWER_H__
#define __SHOOT_POWER_H__

#include <iostream>
#include <SDL2/SDL.h>
#include "drawable.h"

namespace View {
  class ShootPower: public Drawable {
    private:
      int maxTimeShoot;
      int whiteTickness;

    public:
      ShootPower(int w, int h, int time);
      ~ShootPower();
      virtual int getWidth(void) const;
      virtual int getHeight(void) const;
      virtual int getX(void) const;
      virtual int getY(void) const;
      virtual void setX(int);
      virtual void setY(int);
      virtual void render(SDL_Renderer *, int, int);
      void render(SDL_Renderer *, int timeShooting);
  };
}

#endif