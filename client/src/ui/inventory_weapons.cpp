#include "inventory.h"
#include "inventory_weapons.h"

View::WeaponsInventory::WeaponsInventory(SDL_Renderer * r) :
  font(PATH_FONT_ARIAL_BOLD, TEXT_SUPPLIES_SIZE) {
  ItemIcon * icon = new ItemIcon;

  icon->texture.loadFromFile(PATH_ICON_BAZOOKA, r);
  icon->selected = true;
  icon->supplies = 10; // Supplies se recibira por archivo de cfg
  icon->itemName = WEAPON_NAME_BAZOOKA;
  this->items.push_back(icon);

  icon = new ItemIcon;
  icon->texture.loadFromFile(PATH_ICON_MORTAR, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->itemName = WEAPON_NAME_MORTAR;
  this->items.push_back(icon);

  icon = new ItemIcon;
  icon->texture.loadFromFile(PATH_ICON_GREEN_GRENADE, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->itemName = WEAPON_NAME_GREEN_GRENADE;
  this->items.push_back(icon);

  icon = new ItemIcon;
  icon->texture.loadFromFile(PATH_ICON_RED_GRENADE, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->itemName = WEAPON_NAME_RED_GRENADE;
  this->items.push_back(icon);

  icon = new ItemIcon;
  icon->texture.loadFromFile(PATH_ICON_BANANA, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->itemName = WEAPON_NAME_BANANA;
  this->items.push_back(icon);

  icon = new ItemIcon;
  icon->texture.loadFromFile(PATH_ICON_HOLY_GRENADE, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->itemName = WEAPON_NAME_HOLY_GRENADE;
  this->items.push_back(icon);

  icon = new ItemIcon;
  icon->texture.loadFromFile(PATH_ICON_DYNAMITE, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->itemName = WEAPON_NAME_DYNAMITE;
  this->items.push_back(icon);

  icon = new ItemIcon;
  icon->texture.loadFromFile(PATH_ICON_BASEBALL, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->itemName = WEAPON_NAME_BASEBALL;
  this->items.push_back(icon);

  icon = new ItemIcon;
  icon->texture.loadFromFile(PATH_ICON_AIR_STRIKE, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->itemName = WEAPON_NAME_AIR_STRIKE;
  this->items.push_back(icon);

  icon = new ItemIcon;
  icon->texture.loadFromFile(PATH_ICON_TELEPORT, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->itemName = WEAPON_NAME_TELEPORT;
  this->items.push_back(icon);

  this->open = false;

  // Tamanio de la imagen de los iconos
  /* this->iconWidth = this->items.back()->texture.getWidth();
  this->iconHeight = this->items.back()->texture.getHeight(); */

  // Tamanio grande hardcodeado
  this->iconWidth = 60;
  this->iconHeight = 60;
}

View::WeaponsInventory::~WeaponsInventory() {
  for (size_t i = 0 ; i < this->items.size() ; i++) {
    delete this->items[i];
  }
}

void View::WeaponsInventory::render(SDL_Renderer * renderer) {
  if (this->open) {
    int row = 0;

    std::vector<ItemIcon *>::iterator it = this->items.begin();
    while (it != this->items.end()) {
      for (size_t i = 0 ; i < MAX_COLS ; i++) {
        if (it == this->items.end()) {
          break;
        }
        // MAGIA OSCURA:
        // X e Y seran respecto de la camara
        (*it)->texture.render(renderer, this->xOffset + i * this->iconWidth, this->yOffset + row * this->iconHeight, this->iconWidth, this->iconHeight);

        if ((*it)->selected) {
          this->renderItemSelected(renderer, this->xOffset, this->yOffset + row * this->iconHeight, *it);
        }

        it++;
      }
      row++;
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

  this->suppliesTexture.render(renderer, x + this->iconWidth + PADDING * 2, y + this->iconHeight / 2 - (this->suppliesTexture.getHeight() + PADDING * 2) / 2 + PADDING);
}

void View::WeaponsInventory::handleEvent(SDL_Event & e) {
  if (e.type == SDL_KEYDOWN) {
    // Si es Q y el inventario esta abierto
    // elige el arma siguiente
    if (e.key.keysym.sym == SDLK_q) {
      if (this->isOpen()) {
        this->pickNextItem();
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
    for (size_t i = 0 ; i < this->items.size() ; i++) {
      ItemIcon * current = this->items[i];
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
    }
  }
}

bool View::WeaponsInventory::isMouseOnInventoryRanges(int x, int y) {
  return (
    (this->xOffset < x) && 
    (x < this->xOffset + this->iconWidth) &&
    (y > this->yOffset) &&
    (y < this->yOffset + (int)this->items.size() * this->iconHeight)
  );
}

