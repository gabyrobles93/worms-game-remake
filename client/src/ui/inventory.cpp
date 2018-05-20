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
}

View::Inventory::~Inventory() {
  for (size_t i = 0 ; i < this->items.size() ; i++) {
    delete this->items[i];
  }
}

void View::Inventory::render(SDL_Renderer * renderer, int x, int y) {
  int row = 0;
  int col = 0;
  int iconWidth = this->items.back()->texture.getWidth();
  int iconHeight = this->items.back()->texture.getHeight();

  std::vector<View::WeaponIcon *>::iterator it = this->items.begin();
  while (it != this->items.end()) {
    for (size_t i ; i < MAX_COLS ; i++) {
      if (it == this->items.end()) {
        break;
      }
      (*it)->texture.render(renderer, x + i * iconWidth, y + row * iconHeight);
    }
    row++;
  }
  
}