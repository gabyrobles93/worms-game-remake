#include "inventory.h"

View::Inventory::Inventory(SDL_Renderer * r) {
  WeaponIcon * icon = new WeaponIcon;

  icon->texture.loadFromFile(PATH_ICON_BAZOOKA, r);
  icon->selected = true;
  icon->supplies = 10; // Supplies se recibira por archivo de cfg
  icon->weaponName = WEAPON_NAME_BAZOOKA;
  this->items.push_back(icon);

  icon = new WeaponIcon;
  icon->texture.loadFromFile(PATH_ICON_MORTAR, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->weaponName = WEAPON_NAME_MORTAR;
  this->items.push_back(icon);

  icon = new WeaponIcon;
  icon->texture.loadFromFile(PATH_ICON_GREEN_GRENADE, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->weaponName = WEAPON_NAME_GREEN_GRENADE;
  this->items.push_back(icon);

  icon = new WeaponIcon;
  icon->texture.loadFromFile(PATH_ICON_RED_GRENADE, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->weaponName = WEAPON_NAME_RED_GRENADE;
  this->items.push_back(icon);

  icon = new WeaponIcon;
  icon->texture.loadFromFile(PATH_ICON_BANANA, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->weaponName = WEAPON_NAME_BANANA;
  this->items.push_back(icon);

  icon = new WeaponIcon;
  icon->texture.loadFromFile(PATH_ICON_HOLY_GRENADE, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->weaponName = WEAPON_NAME_HOLY_GRENADE;
  this->items.push_back(icon);

  icon = new WeaponIcon;
  icon->texture.loadFromFile(PATH_ICON_DYNAMITE, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->weaponName = WEAPON_NAME_DYNAMITE;
  this->items.push_back(icon);

  icon = new WeaponIcon;
  icon->texture.loadFromFile(PATH_ICON_BASEBALL, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->weaponName = WEAPON_NAME_BASEBALL;
  this->items.push_back(icon);

  icon = new WeaponIcon;
  icon->texture.loadFromFile(PATH_ICON_AIR_STRIKE, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->weaponName = WEAPON_NAME_AIR_STRIKE;
  this->items.push_back(icon);

  icon = new WeaponIcon;
  icon->texture.loadFromFile(PATH_ICON_TELEPORT, r);
  icon->selected = false;
  icon->supplies = 10;
  icon->weaponName = WEAPON_NAME_TELEPORT;
  this->items.push_back(icon);

  this->open = false;
}

View::Inventory::~Inventory() {
  for (size_t i = 0 ; i < this->items.size() ; i++) {
    delete this->items[i];
  }
}

void View::Inventory::render(SDL_Renderer * renderer, int x, int y) {
  if (this->open) {
    int row = 0;
    int iconWidth = this->items.back()->texture.getWidth();
    int iconHeight = this->items.back()->texture.getHeight();

    std::vector<View::WeaponIcon *>::iterator it = this->items.begin();
    while (it != this->items.end()) {
      for (size_t i = 0 ; i < MAX_COLS ; i++) {
        if (it == this->items.end()) {
          break;
        }
        // MAGIA OSCURA:
        // X e Y seran respecto de la camara
        (*it)->texture.render(renderer, x + i * iconWidth, y + row * iconHeight);

        if ((*it)->selected) {
          SDL_Rect outlineRect = { 
            x + (int)i * iconWidth,
            y + row * iconHeight,
            iconWidth, 
            iconHeight
          };
          // Color verde
          SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF); 
          // Dibujamos rectangulo verde en arma seleccionada       
          SDL_RenderDrawRect(renderer, &outlineRect);
        }

        it++;
      }
      row++;
    }
  }
}

void View::Inventory::toggleOpen(void) {
  this->open = !this->open;
}

void View::Inventory::pickNextWeapon(void) {
  for (size_t i = 0; i < this->items.size() ; i++) {
    if (this->items.at(i)->selected == true) {
      if (i == this->items.size() - 1) {
        this->items.back()->selected = false;
        this->items.front()->selected = true;
      } else {
        this->items.at(i)->selected = false;
        this->items.at(i+1)->selected = true;
      }
      break;
    }
  }
}

bool View::Inventory::isOpen(void) const {
  return this->open;
}