#ifndef __INVENTORY_WEAPONS_H__
#define __INVENTORY_WEAPONS_H__

#include <SDL2/SDL.h>
#include "inventory.h"

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

#define MAX_COLS 4

namespace View {
  class WeaponsInventory: public Inventory {
    private:
    public:
      // Constructor por default con todas las armas
      WeaponsInventory(SDL_Renderer *);

      // Destructor
      ~WeaponsInventory();

      virtual void render(SDL_Renderer *);

  };
}

#endif