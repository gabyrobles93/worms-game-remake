#include "map_state.h"

MapState::MapState() {
}

MapState::~MapState() {
  for (std::map<int, View::GirderShort*>::iterator it = this->shortGirders.begin(); 
  it != this->shortGirders.end();
  ++it) {
    delete it->second;
  }

  for (std::map<int, View::GirderLong*>::iterator it = this->longGirders.begin();
  it != this->longGirders.end();
  ++it) {
    delete it->second;
  }

  for (std::map<std::size_t, std::vector<View::Worm*>>::iterator it = this->worms.begin();
  it != this->worms.end();
  ++it) {
    std::vector<View::Worm*>::iterator vector_it = it->second.begin();
    for (;vector_it != it->second.end(); vector_it++) {
      delete *vector_it;
    }
  }
}

std::map<int, View::GirderShort*> MapState::getShortGirders() {
  return this->shortGirders;
}

std::map<int, View::GirderLong*> MapState::getLongGirders() {
  return this->longGirders;
}

std::map<std::size_t, std::vector<View::Worm*>> MapState::getWorms() {
  return this->worms;
}

void MapState::operator=(MapState* mapState) {
  this->shortGirders = mapState->getShortGirders();
  this->longGirders = mapState->getLongGirders();
  this->worms = mapState->getWorms();
}

void MapState::addShortGirder(SDL_Renderer* renderer, degrees_t degrees, int x, int y) {
  View::GirderShort * newShortGirder = new View::GirderShort(renderer, degrees);
  newShortGirder->setX(x);
  newShortGirder->setY(y);
  this->shortGirders.insert(std::pair<int, View::GirderShort*>(this->shortGirders.size() + 1, 
    newShortGirder));
}

void MapState::addLongGirder(SDL_Renderer* renderer, degrees_t degrees, int x, int y) {
  View::GirderLong * newLongGirder = new View::GirderLong(renderer, degrees);
  newLongGirder->setX(x);
  newLongGirder->setY(y);
  
  this->longGirders.insert(std::pair<int, View::GirderLong*>(this->longGirders.size() + 1,
  newLongGirder));
}

void MapState::addWorm(SDL_Renderer* renderer, int teamId, std::string & name, int health, int x, int y) {
  View::Worm * newWorm = new View::Worm(renderer, name, teamId, health);
  newWorm->setX(x);
  newWorm->setY(y);
  this->worms[teamId].push_back(newWorm);
}


void MapState::render(SDL_Renderer * renderer, int camX, int camY) {
  // Render short girders
  std::map<int, View::GirderShort*>::iterator shortGirder;
  for (shortGirder = this->shortGirders.begin(); shortGirder != this->shortGirders.end(); ++shortGirder) {
    shortGirder->second->render(renderer, camX, camY);
  }

  // Render long girders
  std::map<int, View::GirderLong*>::iterator longGirder;
  for (longGirder = this->longGirders.begin(); longGirder != this->longGirders.end(); ++longGirder) {
    longGirder->second->render(renderer, camX, camY);
  }

  // Render worms
  std::map<std::size_t, std::vector<View::Worm*>>::iterator worm;
  for (worm = worms.begin(); worm != worms.end(); ++worm) {
    std::vector<View::Worm*>::iterator worm_it;
    for (worm_it = worm->second.begin(); worm_it != worm->second.end(); worm_it++) {
      (*worm_it)->render(renderer, camX, camY);
    }
  }
}