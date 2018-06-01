#ifndef __INVENTORY_EDITOR_H__
#define __INVENTORY_EDITOR_H__

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "font.h"
#include "inventory.h"
#include "map_game.h"
#include "paths.h"
#include "sound_effect.h"
#include "texture.h"
#include "yaml.h"

#define WEAPON_NAME_SHORT_GIRDER "Short girder"
#define WEAPON_NAME_LONG_GIRDER "Long girder"

#define AMOUNT_WORMS_PER_TEAM 3
#define PADDING 5

#define POS_GIRDER_SHORT 0
#define POS_GIRDER_LONG 1
#define POS_FIRST_WORMS_TEAM 2

#define TEXT_SUPPLIES_SIZE 15

namespace View {
  class MapGame;

  class EditorInventory: public Inventory {
    private:
      size_t amountTeams;
      degrees_t girdersDegrees;
      int wormsHealth;

      Font font;
      Texture suppliesTexture;

      SoundEffect girderClick;
      SoundEffect wormClick;

      // Devuelve el indice del item seleccionado
      int getIndexSelected(void);

      // Dibuja rect blanco en item seleccionado y el texto de supplies
      void renderItemSelected(SDL_Renderer *, int, int, ItemIcon *);

      // Handlea el click izquierdo del mouse
      virtual void handleClick(void);

      // Checkea si el mouse esta en las
      // dimensiones del dibujo del inventario
      virtual bool isMouseOnInventoryRanges(int, int);

    public:
      // Constructor por default con todas las armas
      EditorInventory(SDL_Renderer *, size_t, int);

      // Destructor
      ~EditorInventory();

      virtual void render(SDL_Renderer *);

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