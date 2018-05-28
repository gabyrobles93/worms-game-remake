#include "inventory.h"

View::Inventory::~Inventory(void) {
  
}

void View::Inventory::toggleOpen(void) {
  this->open = !this->open;
}

void View::Inventory::pickNextItem(void) {
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

void View::Inventory::handleEvent(SDL_Event & e) {
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
}
          