#ifndef __GIRDER_H__
#define __GIRDER_H__

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include "texture.h"

#define DIFF_POS 9

typedef enum {
  NINETY_DEGREES = 90,
  SIXTY_DEGREES = 60,
  FORTYFIVE_DEGREES = 45,
  THIRTY_DEGREES = 30,
  ZERO_DEGREES = 0,
  NEGATIVE_THIRTY_DEGREES = -30,
  NEGATIVE_FORTYFIVE_DEGREES = -45,
  NEGATIVE_SIXTY_DEGREES = -60,
  NEGATIVE_NINETY_DEGREES = -90,
} degrees_t;

namespace View {
  class Girder: public Drawable {
    protected:
      std::map<int, Texture> textures;
      std::size_t currentDegrees;
      Texture currentTexture;

    public:
      virtual ~Girder(void);
      void rotateClockwise(void);
      void rotateCounterClockwise(void);
      degrees_t getCurrentDegrees(void);
      virtual int getWidth() const;
      virtual int getHeight() const;
      virtual int getX(void) const;
      virtual int getY(void) const;
      virtual void setX(int);
      virtual void setY(int);
      virtual void render(SDL_Renderer *, int, int);
  };
}

#endif