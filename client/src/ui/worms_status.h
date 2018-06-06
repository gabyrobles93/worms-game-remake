#ifndef __WORMS_STATUS_H__
#define __WORMS_STATUS_H__

#include <SDL2/SDL.h>
#include <map>
#include "yaml.h"
#include "worm.h"
#include "camera.h"

namespace View {
    class WormsStatus;
}

class View::WormsStatus {
    private:
         std::map<size_t, View::Worm *> worms;
    public:
        ~WormsStatus(void);
        WormsStatus(YAML::Node &, SDL_Renderer * r);
        void render(SDL_Renderer *, View::Camera &);
        void update(const YAML::Node &);
        void updateWormProtagonic(size_t);
};

#endif