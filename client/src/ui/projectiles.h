#ifndef __PROJECTILES_H__
#define __PROJECTILES_H__

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include "camera.h"
#include "green_grenade.h"
#include "dynamite.h"
#include "holy_grenade.h"
#include "banana.h"
#include "bazooka.h"
#include "projectil.h"
#include "air_strike.h"
#include "cluster.h"
#include "types.h"
#include "yaml.h"
#include "view_exceptions.h"
#include "inventory_weapons.h"

namespace View {
  class Projectiles {
    private:
      std::map<size_t, Projectil *> projectiles;

      // Crea un proyectil nuevo dependiendo el tipo
      void createProjectil(SDL_Renderer *, int, const YAML::Node &);

      // Libera la memoria de los proyectiles que ya terminaron de usarse
      void cleanProjectilesFinished(void);

    public:
      Projectiles();
      ~Projectiles();
      void render(SDL_Renderer *, Camera &);
      void update(SDL_Renderer *, const YAML::Node &);

      // Devuelve la vista del proyectil protagonico
      // en caso de no haber proyectiles devuelve NULL
      const View::Projectil * getProjectilProtagonic(void);
  };
}

#endif