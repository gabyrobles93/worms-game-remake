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

// El click esta programado para funcionar
// con un inventario de columna unica
#define MAX_COLS 1

namespace View {
  class WeaponsInventory: public Inventory {
    private:
      // Handlea el click izquierdo del mouse
      virtual void handleClick(void);

      // Checkea si el mouse esta en las
      // dimensiones del dibujo del inventario
      virtual bool isMouseOnInventoryRanges(int, int);

    public:
      // Constructor por default con todas las armas
      WeaponsInventory(SDL_Renderer *);

      // Destructor
      ~WeaponsInventory();

      virtual void render(SDL_Renderer *);

      // Handlea un evento
      void handleEvent(SDL_Event &);
  };
}

#endif