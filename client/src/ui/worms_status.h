#ifndef __WORMS_STATUS_H__
#define __WORMS_STATUS_H__

#include <SDL2/SDL.h>
#include <map>
#include "yaml.h"
#include "worm.h"
#include "camera.h"
#include "client_configuration.h"

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
        void updateWormsClientConfiguration(ClientConfiguration &);

        // Devuelve un puntero constante a la vista
        // del worm con el id pasado por parametro
        // en caso de no existir devuelve NULL
        const View::Worm * getWormView(size_t id);
};

#endif