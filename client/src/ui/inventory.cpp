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
          