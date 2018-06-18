#include "inventory.h"

View::Inventory::~Inventory(void) {
  
}

void View::Inventory::toggleOpen(void) {
  this->open = !this->open;
}

bool View::Inventory::isOpen(void) const {
  return this->open;
}
          