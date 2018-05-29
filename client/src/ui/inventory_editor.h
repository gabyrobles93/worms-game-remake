#ifndef __INVENTORY_EDITOR_H__
#define __INVENTORY_EDITOR_H__

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "inventory.h"
#include "map_game.h"
#include "yaml.h"

#define WEAPON_NAME_SHORT_GIRDER "Short girder"
#define WEAPON_NAME_LONG_GIRDER "Long girder"

#define AMOUNT_WORMS_PER_TEAM 3
#define PADDING 5

#define POS_GIRDER_SHORT 0
#define POS_GIRDER_LONG 1
#define POS_FIRST_WORMS_TEAM 2

namespace View {
  class MapGame;

  class EditorInventory: public Inventory {
    private:
      size_t amountTeams;
      degrees_t girdersDegrees;
      int wormsHealth;

      // Devuelve el indice del item seleccionado
      int getIndexSelected(void);

      // Dibuja rect blanco en item seleccionado
      void renderItemSelected(SDL_Renderer *, int, int, int, int);

    public:
      // Constructor por default con todas las armas
      EditorInventory(SDL_Renderer *, size_t, int);

      // Destructor
      ~EditorInventory();

      virtual void render(SDL_Renderer *, int, int);

      // Dibuja el item elegido en la posicion del mouse
      void renderSelectedInMouse(SDL_Renderer *);

      // Se le agrega al inventario del editor
      // que actualice las colecciones de objetos estaticos
      void handleEvent(
        SDL_Renderer *,
        SDL_Event &, 
        View::MapGame &,
        int,
        int
      );

      // Actualiza la cantidad de worms que se pueden poner
      // Este metodo lo utiliza el map game dependiendo de cuantos
      // gusanos hay en el mapa en el estado actual
      void updateWormsTeamSupplies(const YAML::Node &);
  };
}

#endif