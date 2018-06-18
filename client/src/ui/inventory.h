#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "texture.h"
#include "paths.h"
#include "worm.h"
#include "girder_short.h"
#include "girder_long.h"

#define INFINITY_SUPPLIES -1

struct ItemIcon {
  View::Texture texture;
  std::string itemName;
  int supplies;
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

      virtual void handleClick(void) = 0;
      virtual bool isMouseOnInventoryRanges(int, int) = 0;
      
    public:
      virtual ~Inventory();

      // Checkea si el inventario esta abierto
      bool isOpen(void) const;

      // Invierte el estado de 'open'
      void toggleOpen(void);

      // Marca como seleccionada el item siguiente
      virtual void pickNextItem(void) = 0;

      virtual void render(SDL_Renderer *) = 0;
  };
}

#endif