#ifndef __INVENTORY_EDITOR_H__
#define __INVENTORY_EDITOR_H__

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "inventory.h"

#define WEAPON_NAME_SHORT_GIRDER "Short girder"
#define WEAPON_NAME_LONG_GIRDER "Long girder"

namespace View {
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
        std::vector<View::GirderShort*> &, 
        std::vector<View::GirderLong*> &, 
        std::map<std::size_t, std::vector<View::Worm*>> &,
        int,
        int
      );
  };
}

#endif