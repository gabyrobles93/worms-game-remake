#include "inventory_editor.h"

View::EditorInventory::EditorInventory(SDL_Renderer * r, size_t amountTeams, int healthConfig) :
  amountTeams(amountTeams), font(gPath.PATH_FONT_ARIAL_BOLD, TEXT_SUPPLIES_SIZE) {
  
  // Short girder
  ItemIcon * icon = new ItemIcon;
  icon->texture.loadFromFile(gPath.PATH_ICON_SHORT_GIRDER, r);
  icon->selected = true;
  icon->supplies = INFINITY_SUPPLIES;
  icon->itemName = WEAPON_NAME_SHORT_GIRDER;
  this->items.push_back(icon);

  icon = new ItemIcon;
  icon->texture.loadFromFile(gPath.PATH_ICON_LONG_GIRDER, r);
  icon->selected = false;
  icon->supplies = INFINITY_SUPPLIES;
  icon->itemName = WEAPON_NAME_LONG_GIRDER;
  this->items.push_back(icon);

  // Worms teams
  for (size_t i = 1 ; i <= amountTeams ; i++) {
    icon = new ItemIcon;
    icon->texture.loadFromFile(gPath.PATH_PLAIN_WORM, r);
    icon->selected = false;
    icon->supplies = AMOUNT_WORMS_PER_TEAM;
    icon->itemName = std::to_string(i); // Team ID
    this->items.push_back(icon);
  }

  this->open = false;
  this->girdersDegrees = ZERO_DEGREES;
  this->wormsHealth = healthConfig;

  this->iconWidth = this->items.back()->texture.getWidth();
  this->iconHeight = this->items.back()->texture.getHeight();
}

View::EditorInventory::~EditorInventory() {
  for (size_t i = 0 ; i < this->items.size() ; i++) {
    delete this->items[i];
  }
}

void View::EditorInventory::render(SDL_Renderer * r) {
  if (this->open) {
    SDL_Color colors[] = {
      {0, 0, 0, 0},
      {255, 0, 0, 0},
      {0, 255, 0, 0},
      {0, 0, 255, 0}
    };

    std::vector<ItemIcon *>::iterator it = this->items.begin();

    // Render short girder
    (*it)->texture.render(r, this->xOffset, this->yOffset, this->iconWidth, this->iconHeight);
    if ((*it)->selected) {
      this->renderItemSelected(r, this->xOffset, this->yOffset, *it);
    }
    it++;

    (*it)->texture.render(r, this->xOffset, this->yOffset + this->iconHeight, this->iconWidth, this->iconHeight);
    if ((*it)->selected) {
      this->renderItemSelected(r, this->xOffset, this->yOffset + this->iconHeight, *it);
    }
    it++;

    for (int i = POS_FIRST_WORMS_TEAM ; it != this->items.end() ; it++, i++) {
      size_t teamId = std::stoi((*it)->itemName);

      // Black rect
      SDL_Rect blackRect = {
        this->xOffset,
        this->yOffset + i * this->iconHeight,
        this->iconWidth,
        this->iconHeight
      };
      SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xFF);        
      SDL_RenderFillRect(r, &blackRect);

      // Color rect
      SDL_Rect colorRect = {
        this->xOffset + PADDING,
        this->yOffset + i * this->iconHeight + PADDING,
        this->iconWidth - 2 * PADDING,
        this->iconHeight - 2 * PADDING
      };
      SDL_SetRenderDrawColor(r, colors[teamId].r, colors[teamId].g, colors[teamId].b, 0xFF);
      SDL_RenderFillRect(r, &colorRect);

      // Worm icon
      (*it)->texture.render(r, this->xOffset, this->yOffset + i * this->iconHeight);

      if ((*it)->selected) {
        this->renderItemSelected(r, this->xOffset, this->yOffset + i * this->iconHeight, *it);
      } 
    }
  }
}

void View::EditorInventory::renderItemSelected(SDL_Renderer * renderer, int x, int y, ItemIcon * item) {
  SDL_Rect outlineRect = { 
    x,
    y,
    this->iconWidth, 
    this->iconHeight
  };

  // Color blanco
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); 
  // Dibujamos rectangulo blanco en item seleccionado       
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

void View::EditorInventory::renderSelectedInMouse(SDL_Renderer * r) {
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);

  for (size_t i = 0; i < this->items.size() ; i++) {
    if (this->items.at(i)->selected) {
      // Short girder
      if (i == POS_GIRDER_SHORT) {
        View::GirderShort g(r, this->girdersDegrees);
        g.setX(0);
        g.setY(0);
        g.render(r, -mouseX, -mouseY);
      } else if (i == POS_GIRDER_LONG) {
        View::GirderLong g(r, this->girdersDegrees);
        g.setX(0);
        g.setY(0);
        g.render(r, -mouseX, -mouseY);
      } else {
        if (this->items.at(i)->supplies) {
          std::string name("Worm " + std::to_string(AMOUNT_WORMS_PER_TEAM - this->items.at(i)->supplies + 1));
          View::Worm w(r, name, std::stoi(this->items.at(i)->itemName), this->wormsHealth);
          w.setX(0);
          w.setY(0);
          w.render(r, -mouseX, -mouseY);
        }        
      }
    }
  }
}

// Evite mirar y entender este metodo
// puede causar migraña
void View::EditorInventory::handleEvent(
  SDL_Renderer * r,
  SDL_Event & e,
  View::MapGame & map, 
  int camX,
  int camY
  ) {

  if (e.type == SDL_KEYDOWN) {
    // Si es Q y el inventario esta abierto
    // elige el arma siguiente
    if (e.key.keysym.sym == SDLK_q) {
      if (this->isOpen()) {
        this->pickNextItem();
      }
    } 
    // Si es R y el inventario esta abierto
    // rotamos las vigas (para usuarios sin ruedita)
    if (e.key.keysym.sym == SDLK_r) {
      if (this->isOpen()) {
        View::GirderShort g(r, this->girdersDegrees);
        g.rotateClockwise();
        this->girdersDegrees = g.getCurrentDegrees();
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

  // Rotamos el dibujo de las vigas
  if (e.type == SDL_MOUSEWHEEL) {
    if (e.wheel.y > 0) {
      View::GirderShort g(r, this->girdersDegrees);
      g.rotateClockwise();
      this->girdersDegrees = g.getCurrentDegrees();
    }
    if (e.wheel.y < 0) {
      View::GirderShort g(r, this->girdersDegrees);
      g.rotateCounterClockwise();
      this->girdersDegrees = g.getCurrentDegrees();
    }
  }

  // Click izquierdo actualiza la coleccion de objetos estaticos
  if (e.type == SDL_MOUSEBUTTONDOWN) {
    if (e.button.button == SDL_BUTTON_LEFT) {
      int mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);

      size_t index = this->getIndexSelected();
      
      if (index == POS_GIRDER_SHORT) {
        map.addShortGirder(this->girdersDegrees, camX + mouseX, camY + mouseY);		
      } else if (index == POS_GIRDER_LONG) {
        map.addLongGirder(this->girdersDegrees, camX + mouseX, camY + mouseY);
      } else {
        if (this->items.at(index)->supplies) {
          int teamId = std::stoi(this->items.at(index)->itemName);
          std::string name("Worm " + std::to_string(AMOUNT_WORMS_PER_TEAM - this->items.at(index)->supplies + 1));
          map.addWormInTeam(teamId, name, this->wormsHealth, camX + mouseX, camY + mouseY);
          this->items.at(index)->supplies--;
        }
        
      }
    }
  }
}

void View::EditorInventory::handleClick(void) {
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

bool View::EditorInventory::isMouseOnInventoryRanges(int x, int y) {
  return (
    (this->xOffset < x) && 
    (x < this->xOffset + this->iconWidth) &&
    (y > this->yOffset) &&
    (y < this->yOffset + (int)this->items.size() * this->iconHeight)
  );
}

int View::EditorInventory::getIndexSelected(void) {
  for (size_t i = 0 ; i < this->items.size() ; i++) {
    if (this->items.at(i)->selected) {
      return i;
    }
  }
  return -1;
}

void View::EditorInventory::updateWormsTeamSupplies(const YAML::Node & wormsNode) {
  std::map<int, size_t> teams;
  for (size_t i = 1 ; i <= this->amountTeams ; i++) {
    teams[i] = 0;
  }

  YAML::const_iterator it = wormsNode.begin();
  for (; it != wormsNode.end() ; it++) {
    const YAML::Node & eachWorm = *it;
    teams[eachWorm["team"].as<int>()]++;
  }

  for (size_t i = 0 ; i < this->amountTeams ; i++) {
    ItemIcon * wormTeam = this->items[i + POS_FIRST_WORMS_TEAM];
    wormTeam->supplies = AMOUNT_WORMS_PER_TEAM - teams[std::stoi(wormTeam->itemName)];
  }
}
