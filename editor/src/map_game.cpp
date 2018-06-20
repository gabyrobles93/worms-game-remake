#include "map_game.h"

View::MapGame::MapGame(YAML::Node & map) :
map(map) {
  this->index = 0;
}

View::MapGame::~MapGame() {
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

void View::MapGame::setRenderer(SDL_Renderer * renderer) {
  this->renderer = renderer;
}

void View::MapGame::render(SDL_Renderer * renderer, int camX, int camY) {
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
/* Add methods */
void View::MapGame::addShortGirder(degrees_t degrees, int x, int y) {
  this->index++;
  View::GirderShort * newShortGirder = new GirderShort(renderer, degrees);
  newShortGirder->setX(x);
  newShortGirder->setY(y);

  this->shortGirders.insert(std::pair<int, View::GirderShort*>(this->index, 
    newShortGirder));
}

void View::MapGame::addLongGirder(degrees_t degrees, int x, int y) {
  this->index++;
  View::GirderLong * newLongGirder = new GirderLong(renderer, degrees);
  newLongGirder->setX(x);
  newLongGirder->setY(y);
  
  this->longGirders.insert(std::pair<int, View::GirderLong*>(this->index,
  newLongGirder));
}

void View::MapGame::addWormInTeam(int teamId, std::string & name, int health, int x, int y) {
  View::Worm * newWorm = new Worm(renderer, name, teamId, health);
  newWorm->setX(x);
  newWorm->setY(y);

  this->worms[teamId].push_back(newWorm);
}

void View::MapGame::setPreviousState(View::EditorInventory & inv) {
  // if (this->stateIndex) {
  //   this->stateIndex--;
  //   YAML::Node * currentState = this->mapStates[this->stateIndex];
  //   const YAML::Node & wormsTeams = (*currentState)["dynamic"]["worms_teams"];
  //   inv.updateWormsTeamSupplies(wormsTeams);
  // }
}

void View::MapGame::setNextState(View::EditorInventory & inv) {
  // if (this->stateIndex != this->mapStates.size() - 1) {
  //   this->stateIndex++;
  //   YAML::Node * currentState = this->mapStates[this->stateIndex];
  //   const YAML::Node & wormsTeams = (*currentState)["dynamic"]["worms_teams"];
  //   inv.updateWormsTeamSupplies(wormsTeams);
  // }
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
  int longGirderCounter = 1;
  std::map<int, View::GirderLong*>::iterator longGirder;
  for (longGirder = this->longGirders.begin(); longGirder != this->longGirders.end(); ++longGirder) {
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
  int shortGirderCounter = 1;
  std::map<int, View::GirderShort*>::iterator shortGirder;
  for (shortGirder = this->shortGirders.begin(); shortGirder != this->shortGirders.end(); ++shortGirder) {
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
  int wormCounter = 1;
  std::map<std::size_t, std::vector<View::Worm*>>::iterator worm;
  for (worm = worms.begin(); worm != worms.end(); ++worm) {
    std::vector<View::Worm*>::iterator worm_it;
    for (worm_it = worm->second.begin(); worm_it != worm->second.end(); worm_it++) {
      YAML::Node newWorm;
      newWorm["id"] = wormCounter;
      newWorm["name"] = (*worm_it)->getName();
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
  if (this->worms.size() != (size_t) teamsAmount) {
    return false;
  }

  std::map<size_t, std::vector<View::Worm*>>::iterator it;

  for (it = this->worms.begin(); it != this->worms.end(); ++it ) {
    if(it->second.size() != amountWormsPerTeam) {
      return false;
    }
  }

  return true;
}