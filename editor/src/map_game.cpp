#include "map_game.h"

#define DEFAULT_SAVED_MAPS_PATH "/usr/etc/worms/maps/"

View::MapGame::MapGame(YAML::Node & map) :
map(map) {
  this->index = 0;
  this->stateIndex = 0;
}

View::MapGame::~MapGame() {
  for(int i = this->mapStates.size() - 1; i >= 0; --i) {
    delete this->mapStates[i];
    this->mapStates[i] = nullptr;
  }
}

void View::MapGame::initializeStates() {
  this->mapStates.push_back(new MapState());

  if (!this->map["dynamic"]) {
    return;
  }

  std::cout << "EXISTE DYNAMIC" << std::endl;

  const YAML::Node& shortGirders = this->map["static"]["short_girders"];
  const YAML::Node& longGirders = this->map["static"]["long_girders"];
  const YAML::Node& wormsTeams = this->map["dynamic"]["worms_teams"];
 
  std::cout << "NODOS CREADO" << std::endl;
  int x = 0;
  int y = 0;

  std::stringstream ss;
  ss << this->map;
  //std::cout << ss.str().c_str() << std::endl;

  for (YAML::const_iterator it = shortGirders.begin(); it != shortGirders.end(); ++it) {
    std::cout << "ITERANDO SOBRE SHORT GIRDERS" << std::endl;
    const YAML::Node & shortGirder = *it;

    std::cout << "TOMANDO DATOS DE SHORT GIRDER" << std::endl;
    x = shortGirder["x"].as<int>();
    y = shortGirder["y"].as<int>();
    std::cout << x << " " << y << std::endl;
    degrees_t degrees = (degrees_t) shortGirder["angle"].as<int>();
    std::cout << "DEGREES " << degrees << std::endl;
    addShortGirder(degrees, x , y);
    std::cout << "SHORT GIRDER AGREGADA" << std::endl;
  }

  for (YAML::const_iterator it = longGirders.begin(); it != longGirders.end(); ++it) {
    const YAML::Node & longGirder = *it;
    x = longGirder["x"].as<int>();
    y = longGirder["y"].as<int>();
    degrees_t degrees = (degrees_t) longGirder["angle"].as<int>();
    addLongGirder(degrees, x, y);
  }

  int tid = 0;
  std::string name;
  int health = 0;

  for (YAML::const_iterator it = wormsTeams.begin(); it != wormsTeams.end(); ++it) {
    tid = it->first.as<int>();
    const YAML::Node& wormsNode = it->second["worms"];
    for (YAML::const_iterator worms = wormsNode.begin(); worms != wormsNode.end(); worms++) {
      const YAML::Node& worm = *worms;
      name = worm["name"].as<std::string>();
      health = worm["health"].as<int>();
      x = worm["x"].as<int>();
      y = worm["y"].as<int>();
      addWormInTeam(tid, name, health, x, y);
    }
  }

}

void View::MapGame::createMapToSave() {
    mapToSave["static"]["background"] = YAML::Clone(map["static"]["background"]);
    //mapToSave["static"]["background"]["file"] = map["static"]["background"]["file"];
    //mapToSave["static"]["background"]["display"] = map["static"]["background"]["display"];
    mapToSave["static"]["water_level"] = map["static"]["water_level"];
    mapToSave["static"]["teams_amount"] = map["static"]["teams_amount"];
    mapToSave["static"]["worms_health"] = map["static"]["worms_health"];

    mapToSave["static"]["init_inventory"] = YAML::Clone(map["static"]["init_inventory"]);
    // mapToSave["static"]["init_inventory"][std::to_string(w_bazooka)]["item_name"] = "Bazooka";
    // mapToSave["static"]["init_inventory"][std::to_string(w_bazooka)]["supplies"] = map["static"]["init_inventory"][std::to_string(w_bazooka)]["supplies"];

    // mapToSave["static"]["init_inventory"][std::to_string(w_mortar)]["item_name"] = "Mortar";
    // mapToSave["static"]["init_inventory"][std::to_string(w_mortar)]["supplies"] = map["static"]["init_inventory"][std::to_string(w_mortar)]["supplies"];

    // mapToSave["static"]["init_inventory"][std::to_string(w_cluster)]["item_name"] = "Cluster";
    // mapToSave["static"]["init_inventory"][std::to_string(w_cluster)]["supplies"] = map["static"]["init_inventory"][std::to_string(w_cluster)]["supplies"];

    // mapToSave["static"]["init_inventory"][std::to_string(w_banana)]["item_name"] = "Banana";
    // mapToSave["static"]["init_inventory"][std::to_string(w_banana)]["supplies"] = map["static"]["init_inventory"][std::to_string(w_banana)]["supplies"];

    // mapToSave["static"]["init_inventory"][std::to_string(w_green_grenade)]["item_name"] = "Grenade";
    // mapToSave["static"]["init_inventory"][std::to_string(w_green_grenade)]["supplies"] = map["static"]["init_inventory"][std::to_string(w_green_grenade)]["supplies"];

    // mapToSave["static"]["init_inventory"][std::to_string(w_holy_grenade)]["item_name"] = "Holy bomb";
    // mapToSave["static"]["init_inventory"][std::to_string(w_holy_grenade)]["supplies"] = map["static"]["init_inventory"][std::to_string(w_holy_grenade)]["supplies"];

    // mapToSave["static"]["init_inventory"][std::to_string(w_dynamite)]["item_name"] = "Dynamite";
    // mapToSave["static"]["init_inventory"][std::to_string(w_dynamite)]["supplies"] = map["static"]["init_inventory"][std::to_string(w_dynamite)]["supplies"];

    // mapToSave["static"]["init_inventory"][std::to_string(w_air_strike)]["item_name"] = "Air Strike";
    // mapToSave["static"]["init_inventory"][std::to_string(w_air_strike)]["supplies"] = map["static"]["init_inventory"][std::to_string(w_air_strike)]["supplies"];

    // mapToSave["static"]["init_inventory"][std::to_string(w_teleport)]["item_name"] = "Teleport";
    // mapToSave["static"]["init_inventory"][std::to_string(w_teleport)]["supplies"] = map["static"]["init_inventory"][std::to_string(w_teleport)]["supplies"];

    // mapToSave["static"]["init_inventory"][std::to_string(w_bat)]["item_name"] = "Bat";
    // mapToSave["static"]["init_inventory"][std::to_string(w_bat)]["supplies"] = map["static"]["init_inventory"][std::to_string(w_bat)]["supplies"];
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
  std::cout << "INDEX UPDATED" << std::endl;
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
      *it = nullptr;
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

void View::MapGame::saveAs(std::string mapName, std::string bgName, std::string bgPath) {
  addMaxWormsAmount();
  addShortGirdersToMap();  
  addLongGirdersToMap();
  addWormsToMap();
  std::ofstream fout("/usr/etc/worms/maps/map.yml", std::ofstream::trunc);
  std::string bg_name = "background.png";
  this->mapToSave["static"]["background"]["file"] = bg_name;
  addInventoryToTeams();
  fout << mapToSave;
  /* std::cout << "This map" << std::endl;
  std::cout << this->map << std::endl; */
  fout.close();

  std::string maps_path(DEFAULT_SAVED_MAPS_PATH);
  std::string cmd_cp_background = "cp  \"" + bgPath + "\" " + maps_path + "background.png";
  std::system(cmd_cp_background.c_str());

  struct stat buffer;
  std::string map_path = maps_path + mapName + ".tar.gz";
  std::cout << "Chequeando si existe el archivo " << map_path << std::endl;
  if (stat(map_path.c_str(), &buffer) == 0) {
    std::string cmd_rm_previous_map = "rm " + map_path;
    std::system(cmd_rm_previous_map.c_str());
    std::cout << "Mapa previo removido." << std::endl;
  }

  std::string cmd_tar_gz = "tar -zcf \"" + maps_path + mapName + ".tar.gz\" --directory=" + maps_path + " map.yml background.png";
  std::system(cmd_tar_gz.c_str());
  std::string cmd_rmv_temp = "rm " + maps_path + "background.png " + maps_path + "map.yml";
  std::system(cmd_rmv_temp.c_str());
  std::cout << "Mapa guardado!" << std::endl;
}

void View::MapGame::addLongGirdersToMap() {
  std::map<int, View::GirderLong*> longGirders = this->mapStates[this->stateIndex]->getLongGirders();
  int longGirderCounter = 1;
  std::map<int, View::GirderLong*>::const_iterator longGirder;
  for (longGirder = longGirders.begin(); longGirder != longGirders.end(); ++longGirder) {
    YAML::Node newGirderNode;
    newGirderNode["id"] = longGirderCounter;
    newGirderNode["x"] = longGirder->second->getX();
    newGirderNode["y"] = longGirder->second->getY();
    newGirderNode["angle"] = (int) longGirder->second->getCurrentDegrees();
    this->mapToSave["static"]["long_girders"].push_back(newGirderNode);
    longGirderCounter++;
  }
}

void View::MapGame::addShortGirdersToMap() {
  std::map<int, View::GirderShort*> shortGirders = this->mapStates[this->stateIndex]->getShortGirders();
  int shortGirderCounter = 1;
  std::map<int, View::GirderShort*>::const_iterator shortGirder;
  for (shortGirder = shortGirders.begin(); shortGirder != shortGirders.end(); ++shortGirder) {
    YAML::Node newGirderNode;
    newGirderNode["id"] = shortGirderCounter;
    newGirderNode["x"] = shortGirder->second->getX();
    newGirderNode["y"] = shortGirder->second->getY();
    newGirderNode["angle"] = (int) shortGirder->second->getCurrentDegrees();
    if (this->mapToSave["static"]["short_girders"][shortGirderCounter])
    this->mapToSave["static"]["short_girders"].push_back(newGirderNode);
    shortGirderCounter++;
  }
}

void View::MapGame::addWormsToMap() {
  std::map<size_t, std::vector<View::Worm*>> worms = this->mapStates[this->stateIndex]->getWorms();
  int wormCounter = 1;
  std::map<std::size_t, std::vector<View::Worm*>>::const_iterator worm;
  for (worm = worms.begin(); worm != worms.end(); ++worm) {
    std::vector<View::Worm*>::const_iterator worm_it;
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
      this->mapToSave["dynamic"]["worms_teams"][worm->first]["worms"].push_back(newWorm);
      wormCounter++;
    }
  }
}

void View::MapGame::addMaxWormsAmount(void) {
  size_t max = 0;
  std::map<std::size_t, std::vector<View::Worm*>>::const_iterator it;
  std::map<size_t, std::vector<View::Worm*>> worms = this->mapStates[this->stateIndex]->getWorms();
  for (it = worms.begin(); it != worms.end(); ++it) {
    if (it->second.size() > max) {
      max = it->second.size();
    }
  }
  this->mapToSave["static"]["max_worms"] = max;
}

void View::MapGame::addInventoryToTeams() {
  YAML::iterator it = mapToSave["dynamic"]["worms_teams"].begin();
  
  for (; it != mapToSave["dynamic"]["worms_teams"].end() ; it++) {
      it->second["inventory"] = YAML::Clone(this->mapToSave["static"]["init_inventory"]);
  }
}

bool View::MapGame::hasWorms() {
  std::map<size_t, std::vector<View::Worm*>> worms = this->mapStates[this->stateIndex]->getWorms();
  if (worms.size() < 2) return false;
  std::map<size_t, std::vector<View::Worm*>>::iterator it;
  for (it = worms.begin(); it != worms.end(); ++it) {
    if (it->second.size() == 0) {
      return false;
    }
  }
  return true;
}

int View::MapGame::amountWormsTeam(int teamId) {
  std::map<size_t, std::vector<View::Worm*>> worms = this->mapStates[this->stateIndex]->getWorms();
  return worms[teamId].size();
}