#ifndef __WATER_H__
#define __WATER_H__

#include <SDL2/SDL.h>
#include "drawable.h"
#include "resources_paths.h"
#include "texture.h"

#define MAX_FRAME 10
#define MAX_NUM_CLIP 9

namespace View {
  class Water: public Drawable {
    private:
      int x;
      int y;
      int width;
      int height;
      Texture texture;
    public:
      Water();
      ~Water();
      void init(SDL_Renderer * r, int x, int y, int levelWidth, int levelHeight, const char * waterPath = NULL);
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