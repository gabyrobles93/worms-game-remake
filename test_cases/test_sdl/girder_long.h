#ifndef __GIRDER_LONG_H__
#define __GIRDER_LONG_H__

#include "girder.h"

namespace View {
  class GirderLong: public Girder {
    private:
    public:
      GirderLong(SDL_Renderer *);
      ~GirderLong();
  };
}

#endif
