#ifndef __PROJECTILES_H__
#define __PROJECTILES_H__

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include "camera.h"
#include "green_grenade.h"
#include "dynamite.h"
#include "projectil.h"
#include "types.h"
#include "yaml.h"
#include "view_exceptions.h"
#include "inventory_weapons.h"

namespace View {
  class Projectiles {
    private:
      std::map<size_t, Projectil *> projectiles;

      // Crea un proyectil nuevo dependiendo el tipo
      void createProjectil(SDL_Renderer *, int, weapon_t, int);

      // Libera la memoria de los proyectiles que ya terminaron de usarse
      void cleanProjectilesFinished(void);

    public:
      Projectiles();
      ~Projectiles();
      void render(SDL_Renderer *, Camera &);
      void update(SDL_Renderer *, const YAML::Node &);
  };
}

#endif