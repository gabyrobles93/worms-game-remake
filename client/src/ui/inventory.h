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

#define WEAPON_NAME_SHORT_GIRDER "Short girder"
#define WEAPON_NAME_LONG_GIRDER "Long girder"

#define MAX_COLS 4

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

      // Atributos para el inventario del editor
      size_t amountTeams;
      
    public:
      // Constructor estandar para un inventario
      // de armas, con las armas indicadas en el 
      // enunciado del tp.
      Inventory(SDL_Renderer * r);

      // Constructor de inventario de editor de
      // mapas. En un futuro se podria separar
      // estas dos clases y que el comportamiento
      // compartido este en una clase padre
      Inventory(SDL_Renderer *, size_t);

      // Destructor
      ~Inventory();
      
      // Checkea si el inventario esta abierto
      bool isOpen(void) const;

      // Invierte el estado de 'open'
      void toggleOpen(void);

      // Marca como seleccionada el arma siguiente
      void pickNextWeapon(void);

      void render(SDL_Renderer *, int, int);

      // Render del inventario del editor de mapas
      void renderEditorInventory(SDL_Renderer *, int, int);

      // Dibuja rect blanco en item seleccionado
      void renderItemSelected(SDL_Renderer *, int, int, int, int);

      // Click derecho abre/cierra el inventario
      // letra Q cambia el item al siguiente si esta abierto
      void handleEvent(SDL_Event &);
  };
}

#endif