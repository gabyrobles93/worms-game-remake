#ifndef __MAP_GAME_H__
#define __MAP_GAME_H__

#include <SDL2/SDL.h>
#include <map>
#include "drawable.h"
#include "girder_short.h"
#include "girder_long.h"
#include "yaml.h"

namespace View {
  class MapGame/*: public Drawable */{
    private:
      std::map<int, GirderShort *> shortGirders;
      std::map<int, GirderLong *> longGirders;
    public:
      MapGame(SDL_Renderer *, YAML::Node &);
      ~MapGame();
      //virtual void render(SDL_Renderer *, int, int);

  };
}

#endif