#ifndef __GIRDER_SHORT_H__
#define __GIRDER_SHORT_H__

#include "girder.h"
#include "paths.h"

namespace View {
  class GirderShort: public Girder {
    private:
    public:
      GirderShort(SDL_Renderer *, int d = ZERO_DEGREES);
      ~GirderShort();
  };
}

#endif
