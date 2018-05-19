#ifndef __GIRDER_SHORT_H__
#define __GIRDER_SHORT_H__

#include "girder.h"
#include "resources_paths.h"

namespace View {
  class GirderShort: public Girder {
    private:
    public:
      GirderShort(SDL_Renderer *, degrees_t d = ZERO_DEGREES);
      ~GirderShort();
  };
}

#endif
