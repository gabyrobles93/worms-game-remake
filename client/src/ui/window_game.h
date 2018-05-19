#ifndef __WINDOW_GAME_H__
#define __WINDOW_GAME_H__

#include <SDL2/SDL.h>
#include <vector>
#include "girder_short.h"
#include "girder_long.h"

namespace View {
  class WindowGame {
    private:
      SDL_Renderer * renderer = NULL;
      SDL_Window* window = NULL;
      // Vector de vigas creadas
      std::vector<View::GirderLong*> longGirders;
      int screen_width;
      int screen_height;

      void init(void);
      bool loadMedia(void);
      void close(void);
      int getWidthResolution(void);
      int getHeightResolution(void);

    public:
      WindowGame(int w = 0, int h = 0);
      ~WindowGame();
      SDL_Renderer * getRenderer(void) const;
      int getWidth(void) const;
      int getHeight(void) const;
  };
};

#endif
