#ifndef __GIRDER_H__
#define __GIRDER_H__

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include "texture.h"

#define DIFF_POS 9

typedef enum {
  NINETY_DEGREES = 0,
  SIXTY_DEGREES = 1,
  FORTYFIVE_DEGREES = 2,
  THIRTY_DEGREES = 3,
  ZERO_DEGREES = 4,
  NEGATIVE_THIRTY_DEGREES = 5,
  NEGATIVE_FORTYFIVE_DEGREES = 6,
  NEGATIVE_SIXTY_DEGREES = 7,
  NEGATIVE_NINETY_DEGREES = 8,
} degrees_t;

namespace View {
  class Girder: public Drawable {
    protected:
      std::map<std::size_t, Texture> textures;
      std::size_t currentDegrees;
      Texture currentTexture;

    public:
      void rotateClockwise(void);
      void rotateCounterClockwise(void);
      degrees_t getCurrentDegrees(void);
      virtual int getWidth();
      virtual int getHeight();
      virtual int getX(void);
      virtual int getY(void);
      virtual void render(SDL_Renderer *, int, int);
  };
}

#endif