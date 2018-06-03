#ifndef __PROJECTILES_H__
#define __PROJECTILES_H__

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include "camera.h"
#include "dynamite.h"
#include "projectil.h"
#include "yaml.h"
#include "view_exceptions.h"
#include "inventory_weapons.h"

typedef enum {
  BAZOOKA,
  MORTAR,
  GREEN_GRENADE,
  RED_GRENADE,
  BANANA,
  HOLY_GRENADE,
  DYNAMITE,
  AIR_STRIKE
} projectil_t;

namespace View {
  class Projectiles {
    private:
      std::map<size_t, Projectil *> projectiles;

      std::map<std::string, projectil_t> projectilesTypes;

      // Crea un proyectil nuevo dependiendo el tipo
      void createProjectil(SDL_Renderer *, int, std::string, int);

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