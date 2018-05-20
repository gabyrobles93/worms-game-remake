#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "texture.h"
#include "resources_paths.h"

#define WEAPON_NAME_BAZOOKA "Bazooka"
#define WEAPON_NAME_MORTAR "Mortar"
#define WEAPON_NAME_GREEN_GRENADE "Grenade"
#define WEAPON_NAME_RED_GRENADE "Cluster"
#define WEAPON_NAME_BANANA "Banana"
#define WEAPON_NAME_HOLY_GRENADE "Holy grenade"
#define WEAPON_NAME_DYNAMITE "Dynamite"
#define WEAPON_NAME_BASEBALL "Baseball bat"
#define WEAPON_NAME_AIR_STRIKE "Air strike"
#define WEAPON_NAME_TELEPORT "Teleport"

#define MAX_COLS 5

namespace View {
  struct WeaponIcon {
    Texture texture;
    std::string weaponName;
    size_t supplies;
    bool selected;
  };

  class Inventory {
    private:
      std::vector<WeaponIcon *> items;
      WeaponIcon selected;
      bool open;

    public:
      Inventory(SDL_Renderer * r);
      Inventory();
      void render(SDL_Renderer *, int, int);
  };
}

#endif