#ifndef __INVENTORY_WEAPONS_H__
#define __INVENTORY_WEAPONS_H__

#include <SDL2/SDL.h>
#include "font.h"
#include "inventory.h"
#include "paths.h"
#include "texture.h"
#include "types.h"
#include "yaml.h"

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

#define TEXT_SUPPLIES_SIZE 15
#define PADDING 5

// El click esta programado para funcionar
// con un inventario de columna unica
#define MAX_COLS 1

namespace View {
  class WeaponsInventory: public Inventory {
    private:
      Font font;
      Texture suppliesTexture;
      std::map<std::string, weapon_t> weapons;
      std::map<weapon_t, std::string> iconPaths;

      // Handlea el click izquierdo del mouse
      virtual void handleClick(void);

      // Checkea si el mouse esta en las
      // dimensiones del dibujo del inventario
      virtual bool isMouseOnInventoryRanges(int, int);

      // Dibuja rect blanco en item seleccionado y el texto de supplies
      void renderItemSelected(SDL_Renderer *, int, int, ItemIcon *);

    public:
      // Constructor por default con todas las armas
      WeaponsInventory(SDL_Renderer *, const YAML::Node &);

      // Destructor
      ~WeaponsInventory();

      virtual void render(SDL_Renderer *);

      // Handlea un evento
      void handleEvent(SDL_Event &);

      // Setea el tamanio de las vistas de los iconos
      void setIconSide(int);

      // Retorna el weapon_t seleccionado
      weapon_t getSelectedWeapon(void);

      // Updatea el inventario con el nodo que envia el server
      void update(const YAML::Node &);
  };
}

#endif