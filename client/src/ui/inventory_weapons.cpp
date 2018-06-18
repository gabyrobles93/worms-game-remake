#include "inventory.h"
#include "inventory_weapons.h"
#include "types.h"
#include <iostream>

View::WeaponsInventory::WeaponsInventory(SDL_Renderer * r, const YAML::Node & initInv) :
  font(gPath.PATH_FONT_ARIAL_BOLD, TEXT_SUPPLIES_SIZE) {

  this->iconPaths[w_bazooka] = gPath.PATH_ICON_BAZOOKA;
  this->iconPaths[w_mortar] = gPath.PATH_ICON_MORTAR;
  this->iconPaths[w_cluster] = gPath.PATH_ICON_RED_GRENADE;
  this->iconPaths[w_green_grenade] = gPath.PATH_ICON_GREEN_GRENADE;
  this->iconPaths[w_banana] = gPath.PATH_ICON_BANANA;
  this->iconPaths[w_holy_grenade] = gPath.PATH_ICON_HOLY_GRENADE;
  this->iconPaths[w_air_strike] = gPath.PATH_ICON_AIR_STRIKE;
  this->iconPaths[w_dynamite] = gPath.PATH_ICON_DYNAMITE;
  this->iconPaths[w_bat] = gPath.PATH_ICON_BASEBALL;
  this->iconPaths[w_teleport] = gPath.PATH_ICON_TELEPORT;

  YAML::const_iterator invIt = initInv.begin();
  bool isFirstItem = true;
  for (; invIt != initInv.end() ; invIt++) {
    ItemIcon * icon = new ItemIcon;
    weapon_t idItem = (weapon_t)invIt->first.as<int>();
    icon->texture.loadFromFile(this->iconPaths[idItem], r);
    icon->supplies = invIt->second["supplies"].as<int>();
    std::string itName(invIt->second["item_name"].as<std::string>());
    icon->itemName = itName;

    if (isFirstItem) {
      icon->selected = true;
      isFirstItem = false;
    } else {
      icon->selected = false;
    }
    
    this->itemsMap[idItem] = icon;
  }

  this->open = false;

  // Tamanio grande hardcodeado
  this->iconWidth = 60;
  this->iconHeight = 60;
}

View::WeaponsInventory::~WeaponsInventory() {
  for (size_t i = 0 ; i < this->items.size() ; i++) {
    delete this->items[i];
  }

  std::map<weapon_t, ItemIcon *>::iterator it = this->itemsMap.begin();
  for (; it != this->itemsMap.end() ; it++) {
    delete it->second;
  }
}

void View::WeaponsInventory::setIconSide(int size) {
  this->iconWidth = size;
  this->iconHeight = size;
}

void View::WeaponsInventory::render(SDL_Renderer * renderer) {
  if (this->open) {
    std::map<weapon_t, ItemIcon *>::iterator itMap = this->itemsMap.begin();
    size_t i = 0;
    for (; itMap != this->itemsMap.end() ; itMap++) {
      itMap->second->texture.render(
        renderer, 
        this->xOffset,
        this->yOffset + i * this->iconHeight,
        this->iconWidth,
        this->iconHeight
      );

      if (itMap->second->selected) {
        this->renderItemSelected(
          renderer,
          this->xOffset,
          this->yOffset + i * this->iconHeight,
          itMap->second
        );
      }

      i++;
    }
  }
}

void View::WeaponsInventory::renderItemSelected(SDL_Renderer * renderer, int x, int y, ItemIcon * item) {
  SDL_Rect outlineRect = { 
    x,
    y,
    this->iconWidth, 
    this->iconHeight
  };
  // Color verde
  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF); 
  // Dibujamos rectangulo verde en arma seleccionada       
  SDL_RenderDrawRect(renderer, &outlineRect);

  // Render text supplies
  SDL_Color white = {255, 255, 255, 0};

  std::string supplies;
  if (item->supplies != INFINITY_SUPPLIES) {
    supplies = std::to_string(item->supplies);
  } else {
    supplies = "oo";
  }
  this->suppliesTexture.loadFromRenderedText(renderer, this->font, "Supplies " + supplies, white);

  SDL_Rect rectSupplies = { 
    x + this->iconWidth + PADDING,
    y + this->iconHeight / 2 - (this->suppliesTexture.getHeight() + PADDING * 2) / 2,
    this->suppliesTexture.getWidth() + PADDING * 2, 
    this->suppliesTexture.getHeight() + PADDING * 2,
  };

  // Color negro
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); 
  // Dibujamos rectangulo negro en item seleccionado       
  SDL_RenderFillRect(renderer, &rectSupplies);

  this->suppliesTexture.render(
    renderer,
    x + this->iconWidth + PADDING * 2, 
    y + this->iconHeight / 2 - (this->suppliesTexture.getHeight() + PADDING * 2) / 2 + PADDING
  );
}

void View::WeaponsInventory::handleEvent(SDL_Event & e) {
  if (e.type == SDL_KEYDOWN) {
    // Si es Q y el inventario esta abierto
    // elige el arma siguiente
    if (e.key.keysym.sym == SDLK_q) {
      if (this->isOpen()) {
        this->pickNextItem();
      } else {
        this->toggleOpen();
      }
    } 

    if (e.key.keysym.sym == SDLK_e) {
      if (this->isOpen()) {
        this->toggleOpen();
      }
    }
  }

  // Click derecho abre o cierra el inventario
  if (e.type == SDL_MOUSEBUTTONDOWN) {
    if (e.button.button == SDL_BUTTON_RIGHT) {
      this->toggleOpen();
    }
  }

  if (e.type == SDL_MOUSEBUTTONDOWN) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    if (
      e.button.button == SDL_BUTTON_LEFT && 
      this->isMouseOnInventoryRanges(mouseX, mouseY) &&
      this->isOpen()
    ) {
      this->handleClick();
      return;
    }
  }
}

void View::WeaponsInventory::handleClick(void) {
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);

  if (this->isMouseOnInventoryRanges(mouseX, mouseY)) {
    std::map<weapon_t, ItemIcon *>::iterator it = this->itemsMap.begin();
    size_t i = 0;
    for (; it != this->itemsMap.end() ; it++) {
      ItemIcon * current = it->second;
      int lowLimit = this->yOffset + i * this->iconHeight;
      int upLimit = lowLimit + this->iconHeight;
      if (current->selected && mouseY > lowLimit && mouseY < upLimit) {
        // Si clickeo el que ya estaba seleccionado no hacemos nada
        break;
      }

      // El seleccionado viejo hay que desseleccionarlo
      if (current->selected) {
        current->selected = false;
      }

      // Y el clickeado hay que seleccionarlo
      if (mouseY > lowLimit && mouseY < upLimit) {
        current->selected = true;
      }
      
      i++;
    }
  }
}

bool View::WeaponsInventory::isMouseOnInventoryRanges(int x, int y) {
  return (
    (this->xOffset < x) && 
    (x < this->xOffset + this->iconWidth) &&
    (y > this->yOffset) &&
    (y < this->yOffset + (int)this->itemsMap.size() * this->iconHeight)
  );
}

weapon_t View::WeaponsInventory::getSelectedWeapon(void) {
  std::map<weapon_t, ItemIcon *>::iterator it = this->itemsMap.begin();
  weapon_t weapon;

  for (; it != this->itemsMap.end() ; it++) {
    if (it->second->selected) {
      weapon = it->first;
      break;
    }
  }

  return weapon;
}

void View::WeaponsInventory::update(const YAML::Node & node) {
  YAML::const_iterator it = node.begin();
  for (; it != node.end() ; it++) {
    weapon_t weaponId = (weapon_t)it->first.as<int>();
    int supplies = it->second["supplies"].as<int>();
    if (supplies) {
      if (this->itemsMap.find(weaponId) != this->itemsMap.end()) {
        this->itemsMap[weaponId]->supplies = supplies;
      }
    } else {
      if (this->itemsMap.find(weaponId) != this->itemsMap.end()) {
        std::map<weapon_t, ItemIcon *>::iterator itMap = this->itemsMap.begin();

        for (; itMap != this->itemsMap.end() ; itMap++) {
          if (itMap->first == weaponId && itMap->second->selected) {
            itMap->second->selected = false;
            itMap++;
            if (itMap != this->itemsMap.end()) {
          
            } else {
              itMap = this->itemsMap.begin();
            }
            itMap->second->selected = true;
          }
        }
        
        delete this->itemsMap[weaponId];
        this->itemsMap.erase(weaponId);
      }
    }
  }
}

void View::WeaponsInventory::pickNextItem(void) {
  std::map<weapon_t, ItemIcon *>::iterator it = this->itemsMap.begin();
  for (; it != this->itemsMap.end() ; it++) {
    if (it->second->selected) {
      it->second->selected = false;
      it++;

      if (it == this->itemsMap.end()) {
        it = this->itemsMap.begin();
      }

      it->second->selected = true;
      break;
    }
  }
}