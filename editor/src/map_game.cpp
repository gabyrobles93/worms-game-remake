#include "map_game.h"

View::MapGame::MapGame(YAML::Node & map) :
map(map) {
  this->index = 0;
  this->mapStates.push_back(new MapState());
  this->stateIndex = 0;
}

View::MapGame::~MapGame() {
  for(int i = 0; i < this->mapStates.size(); ++i) {
    delete this->mapStates[i];
  }
}

void View::MapGame::setRenderer(SDL_Renderer * renderer) {
  this->renderer = renderer;
}

void View::MapGame::render(SDL_Renderer * renderer, int camX, int camY) {
    if (this->mapStates.size() != 0) {
    this->mapStates[stateIndex]->render(renderer, camX, camY);  
  }
}
/* Add methods */
void View::MapGame::addShortGirder(degrees_t degrees, int x, int y) {
  this->updateIndex();
  MapState* previousState = this->mapStates.back();
  MapState* newState = new MapState();
  newState->operator=(previousState);
  newState->addShortGirder(renderer, degrees, x, y);
  this->mapStates.push_back(newState);
}

void View::MapGame::addLongGirder(degrees_t degrees, int x, int y) {
  this->updateIndex();
  MapState* previousState = this->mapStates.back();
  MapState* newState = new MapState();
  newState->operator=(previousState);
  newState->addLongGirder(renderer, degrees, x, y);
  this->mapStates.push_back(newState);
}

void View::MapGame::addWormInTeam(int teamId, std::string & name, int health, int x, int y) {
  this->updateIndex();
  MapState* previousState = this->mapStates.back();
  MapState* newState = new MapState();
  newState->operator=(previousState);
  newState->addWorm(renderer, teamId, name, health, x, y);
  this->mapStates.push_back(newState);
}

void View::MapGame::setPreviousState(View::EditorInventory & inv) {
  if (this->stateIndex) {
    this->stateIndex--;
    inv.updateWormsTeamSupplies(this->mapStates[this->stateIndex]->getWorms());
  }
}

void View::MapGame::setNextState(View::EditorInventory & inv) {
  if (this->stateIndex != this->mapStates.size() - 1) {
    this->stateIndex++;
    inv.updateWormsTeamSupplies(this->mapStates[this->stateIndex]->getWorms());
  }
}

void View::MapGame::updateIndex(void) {
  this->stateIndex++;

  if (this->stateIndex != this->mapStates.size()) {
    std::vector<MapState*>::iterator it = this->mapStates.begin() + this->stateIndex;
    for (; it != this->mapStates.end();) {
      delete *it;
      it = this->mapStates.erase(it);
    }
  }
}

void View::MapGame::printCurrentState(void) {
  // std::cout << *this->mapStates[this->stateIndex] << std::endl;
}

int View::MapGame::getNextWormId(void) {
  // int newId = 1;
  // YAML::Node * state = this->mapStates[this->stateIndex];
  // const YAML::Node & teams = (*state)["dynamic"]["worms_teams"];
  // YAML::const_iterator it = teams.begin();

  // for (; it != teams.end() ; it++) {
  //   newId += (it->second)["worms"].size();
  // }
  
  // return newId;
}

void View::MapGame::saveAs(std::string mapName, std::string bgName) {
  addShortGirdersToMap();  
  addLongGirdersToMap();
  addWormsToMap();
  std::ofstream fout("../maps/map.yml", std::ofstream::trunc);
  std::string bg_name = "background.png";
  this->map["static"]["background"]["file"] = bg_name;
  addInventoryToTeams();
  fout << this->map;
  fout.close();
}

void View::MapGame::addLongGirdersToMap() {
  std::map<int, View::GirderLong*> longGirders = this->mapStates[this->stateIndex]->getLongGirders();
  int longGirderCounter = 1;
  std::map<int, View::GirderLong*>::iterator longGirder;
  for (longGirder = longGirders.begin(); longGirder != longGirders.end(); ++longGirder) {
    YAML::Node newGirderNode;
    newGirderNode["id"] = longGirderCounter;
    newGirderNode["x"] = longGirder->second->getX();
    newGirderNode["y"] = longGirder->second->getY();
    newGirderNode["angle"] = (int) longGirder->second->getCurrentDegrees();
    this->map["static"]["long_girders"].push_back(newGirderNode);
    longGirderCounter++;
  }
}

void View::MapGame::addShortGirdersToMap() {
  std::map<int, View::GirderShort*> shortGirders = this->mapStates[this->stateIndex]->getShortGirders();
  int shortGirderCounter = 1;
  std::map<int, View::GirderShort*>::iterator shortGirder;
  for (shortGirder = shortGirders.begin(); shortGirder != shortGirders.end(); ++shortGirder) {
    YAML::Node newGirderNode;
    newGirderNode["id"] = shortGirderCounter;
    newGirderNode["x"] = shortGirder->second->getX();
    newGirderNode["y"] = shortGirder->second->getY();
    newGirderNode["angle"] = (int) shortGirder->second->getCurrentDegrees();
    this->map["static"]["short_girders"].push_back(newGirderNode);
    shortGirderCounter++;
  }
}

void View::MapGame::addWormsToMap() {
  std::map<size_t, std::vector<View::Worm*>> worms = this->mapStates[this->stateIndex]->getWorms();
  int wormCounter = 1;
  std::map<std::size_t, std::vector<View::Worm*>>::iterator worm;
  for (worm = worms.begin(); worm != worms.end(); ++worm) {
    std::vector<View::Worm*>::iterator worm_it;
    for (worm_it = worm->second.begin(); worm_it != worm->second.end(); worm_it++) {
      YAML::Node newWorm;
      newWorm["id"] = wormCounter;
      newWorm["name"] = (*worm_it)->getName();
      newWorm["health"] = (*worm_it)->getHealth();
      newWorm["x"] = (*worm_it)->getX();
      newWorm["y"] = (*worm_it)->getY();
      newWorm["sight_angle"] = 0;
      newWorm["status"]["grounded"] = 0;
      newWorm["status"]["falling"] = 1;
      newWorm["status"]["mirrored"] = 0;
      newWorm["status"]["walking"] = 0;
      this->map["dynamic"]["worms_teams"][worm->first]["worms"].push_back(newWorm);
      wormCounter++;
    }
  }
}

void View::MapGame::addInventoryToTeams() {
  YAML::iterator it = map["dynamic"]["worms_teams"].begin();
  
  for (; it != map["dynamic"]["worms_teams"].end() ; it++) {
      it->second["inventory"] = YAML::Clone(this->map["static"]["init_inventory"]);
  }
}

bool View::MapGame::hasAllTheWorms(int teamsAmount, int amountWormsPerTeam) {
  std::map<size_t, std::vector<View::Worm*>> worms = this->mapStates[this->stateIndex]->getWorms();
  if (worms.size() != (size_t) teamsAmount) {
    return false;
  }

  std::map<size_t, std::vector<View::Worm*>>::iterator it;

  for (it = worms.begin(); it != worms.end(); ++it ) {
    if(it->second.size() != amountWormsPerTeam) {
      return false;
    }
  }

  return true;
}