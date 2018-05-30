#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "texture.h"
#include "resources_paths.h"
#include "worm.h"
#include "girder_short.h"
#include "girder_long.h"

struct ItemIcon {
  View::Texture texture;
  std::string itemName;
  size_t supplies;
  bool selected;
};

namespace View {
  class Inventory {
    protected:
      std::vector<ItemIcon *> items;
      bool open;
      const int xOffset = 10;
      const int yOffset = 10;
      int iconWidth;
      int iconHeight;
      
    public:
      virtual ~Inventory();

      // Checkea si el inventario esta abierto
      bool isOpen(void) const;

      // Invierte el estado de 'open'
      void toggleOpen(void);

      // Marca como seleccionada el item siguiente
      void pickNextItem(void);

      // Click derecho abre/cierra el inventario
      // letra Q cambia el item al siguiente si esta abierto
      void handleEvent(SDL_Event &);

      virtual void render(SDL_Renderer *) = 0;
  };
}

#endif