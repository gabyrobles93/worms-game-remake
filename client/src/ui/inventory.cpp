#include "inventory.h"

#define AMOUNT_WORMS_PER_TEAM 3
#define PADDING 5

#define POS_GIRDER_SHORT 0
#define POS_GIRDER_LONG 1

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
  this->girdersDegrees = ZERO_DEGREES;
  this->wormsHealth = 0;
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


// Editor de mapas
View::Inventory::Inventory(SDL_Renderer * r, size_t amountTeams, int healthConfig) :
  amountTeams(amountTeams) {
  
  // Short girder
  WeaponIcon * icon = new WeaponIcon;
  icon->texture.loadFromFile(PATH_ICON_SHORT_GIRDER, r);
  icon->selected = true;
  icon->supplies = AMOUNT_WORMS_PER_TEAM;
  icon->weaponName = WEAPON_NAME_SHORT_GIRDER;
  this->items.push_back(icon);

  icon = new WeaponIcon;
  icon->texture.loadFromFile(PATH_ICON_LONG_GIRDER, r);
  icon->selected = false;
  icon->supplies = AMOUNT_WORMS_PER_TEAM;
  icon->weaponName = WEAPON_NAME_LONG_GIRDER;
  this->items.push_back(icon);

  // Worms teams
  for (size_t i = 1 ; i <= amountTeams ; i++) {
    icon = new WeaponIcon;
    icon->texture.loadFromFile(PATH_PLAIN_WORM, r);
    icon->selected = false;
    icon->supplies = AMOUNT_WORMS_PER_TEAM;
    icon->weaponName = std::to_string(i); // Team ID
    this->items.push_back(icon);
  }

  this->open = false;
  this->girdersDegrees = ZERO_DEGREES;
  this->wormsHealth = healthConfig;
}

void View::Inventory::renderEditorInventory(SDL_Renderer * r, int x, int y) {
  if (this->open) {
    SDL_Color colors[] = {
      {0, 0, 0, 0},
      {255, 0, 0, 0},
      {0, 255, 0, 0},
      {0, 0, 255, 0}
    };
   
    std::vector<View::WeaponIcon *>::iterator it = this->items.begin();
    int iconWidth = this->items.back()->texture.getWidth();
    int iconHeight = this->items.back()->texture.getHeight();

    // Render short girder
    (*it)->texture.render(r, x, y, iconWidth, iconHeight);
    if ((*it)->selected) {
      this->renderItemSelected(r, x, y, iconWidth, iconHeight);
    }
    it++;

    (*it)->texture.render(r, x, y + iconHeight, iconWidth, iconHeight);
    if ((*it)->selected) {
      this->renderItemSelected(r, x, y + iconHeight, iconWidth, iconHeight);
    }
    it++;

    for (int i = 2 ; it != this->items.end() ; it++, i++) {
      size_t teamId = std::stoi((*it)->weaponName);

      // Black rect
      SDL_Rect blackRect = {
        x,
        y + i * iconHeight,
        iconWidth,
        iconHeight
      };
      SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xFF);        
      SDL_RenderFillRect(r, &blackRect);

      // Color rect
      SDL_Rect colorRect = {
        x + PADDING,
        y + i * iconHeight + PADDING,
        iconWidth - 2 * PADDING,
        iconHeight - 2 * PADDING
      };
      SDL_SetRenderDrawColor(r, colors[teamId].r, colors[teamId].g, colors[teamId].b, 0xFF);
      SDL_RenderFillRect(r, &colorRect);

      // Worm icon
      (*it)->texture.render(r, x, y + i * iconHeight);

      if ((*it)->selected) {
        this->renderItemSelected(r, x, y + i * iconHeight, iconWidth, iconHeight);
      }   
    }
  }
}

void View::Inventory::renderItemSelected(SDL_Renderer * renderer, int x, int y, int width, int height) {
  SDL_Rect outlineRect = { 
    x,
    y,
    width, 
    height
  };

  // Color blanco
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); 
  // Dibujamos rectangulo blanco en item seleccionado       
  SDL_RenderDrawRect(renderer, &outlineRect);
}

void View::Inventory::renderSelectedInMouse(SDL_Renderer * r) {
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);

  for (size_t i = 0; i < this->items.size() ; i++) {
    if (this->items.at(i)->selected) {
      // Short girder
      if (i == POS_GIRDER_SHORT) {
        View::GirderShort g(r);
        g.setX(0);
        g.setY(0);
        g.render(r, -mouseX, -mouseY);
      } else if (i == POS_GIRDER_LONG) {
        View::GirderLong g(r);
        g.setX(0);
        g.setY(0);
        g.render(r, -mouseX, -mouseY);
      } else {
        if (this->items.at(i)->supplies) {
          std::string name("Worm " + std::to_string(AMOUNT_WORMS_PER_TEAM - this->items.at(i)->supplies + 1));
          View::Worm w(r, name, std::stoi(this->items.at(i)->weaponName), this->wormsHealth);
          w.setX(0);
          w.setY(0);
          w.render(r, -mouseX, -mouseY);
        }        
      }
    }
  }
}

void View::Inventory::handleEvent(SDL_Event & e) {
  if (e.type == SDL_KEYDOWN) {
    // Si es Q y el inventario esta abierto
    // elige el arma siguiente
    if (e.key.keysym.sym == SDLK_q) {
      if (this->isOpen()) {
        this->pickNextWeapon();
      }
    } 
  }

  // Click derecho abre o cierra el inventario
  if (e.type == SDL_MOUSEBUTTONDOWN) {
    if (e.button.button == SDL_BUTTON_RIGHT) {
      this->toggleOpen();
    }
  }
}

// Evite mirar y entender este metodo
// puede causar migraña
void View::Inventory::handleEvent(
  SDL_Renderer * r,
  SDL_Event & e, 
  std::vector<View::GirderShort*> & gs, 
  std::vector<View::GirderLong*> & gl, 
  std::map<std::size_t, std::vector<View::Worm*>> & w,
  int camX,
  int camY
  ) {
  
  this->handleEvent(e);

  // Click izquierdo actualiza la coleccion de objetos estaticos
  if (e.type == SDL_MOUSEBUTTONDOWN) {
    if (e.button.button == SDL_BUTTON_LEFT) {
      int mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);

      size_t index = this->getIndexSelected();
      
      if (index == POS_GIRDER_SHORT) {
        gs.push_back(new View::GirderShort(r, this->girdersDegrees));
        gs.back()->setX(camX + mouseX);
        gs.back()->setY(camY + mouseY);			
      } else if (index == POS_GIRDER_LONG) {
        gl.push_back(new View::GirderLong(r, this->girdersDegrees));
        gl.back()->setX(camX + mouseX);
        gl.back()->setY(camY + mouseY);
      } else {
        if (this->items.at(index)->supplies) {
          int teamId = std::stoi(this->items.at(index)->weaponName);
          std::string name("Worm " + std::to_string(AMOUNT_WORMS_PER_TEAM - this->items.at(index)->supplies + 1));
          w[teamId].push_back(new View::Worm(r, name, teamId, this->wormsHealth));
          w[teamId].back()->setX(camX + mouseX);
          w[teamId].back()->setY(camY + mouseY);
          this->items.at(index)->supplies--;
        }
        
      }
    }
  }
}

int View::Inventory::getIndexSelected(void) {
  for (size_t i = 0 ; i < this->items.size() ; i++) {
    if (this->items.at(i)->selected) {
      return i;
    }
  }
  return -1;
}
          