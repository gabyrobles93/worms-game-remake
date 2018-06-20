#ifndef __WORM_STATE_H__
#define __WORM_STATE_H__

#include <SDL2/SDL.h>
#include "types.h"
#include "paths.h"

namespace View {
  class Worm;

  class WormState {
    protected:
      View::Worm * context;
      view_worm_state_t state;

    public:
      virtual ~WormState() {};
      virtual void render(SDL_Renderer *, int, int, worm_inclination_t, bool, int a = -1) = 0;
      virtual void resetAnimation(void) = 0;
      view_worm_state_t getState(void) {
        return this->state;
      }
  };
}

#endif