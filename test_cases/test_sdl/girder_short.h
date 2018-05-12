#ifndef __GIRDER_SHORT_H__
#define __GIRDER_SHORT_H__

#include "girder.h"

namespace View {
  class GirderShort: public Girder {
    private:
    public:
      GirderShort(SDL_Renderer *);
      ~GirderShort();
  };
}

#endif
