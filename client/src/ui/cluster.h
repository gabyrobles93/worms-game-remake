#ifndef __CLUSTER_H__
#define __CLUSTER_H__

#include <SDL2/SDL.h>
#include "explosion.h"
#include "paths.h"
#include "projectil.h"
#include "rectangle_text.h"


namespace View {
  class Cluster: public Projectil {
    private:
      SpriteAnimation sprite;
      Explosion explosion;
      RectangleText countdownText;

    public:
      Cluster(SDL_Renderer * r, int countdown, int ratioExplosion = 100);
      ~Cluster();

      virtual void render(SDL_Renderer * r, int, int);
  };
}

#endif