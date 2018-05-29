#include "map_game.h"

View::MapGame::MapGame(YAML::Node & map) {
  this->mapStates.push_back(new YAML::Node);
  (*this->mapStates.back()) = map;

  this->stateIndex = this->mapStates.size() - 1;
}

View::MapGame::~MapGame() {
  for (size_t i = 0 ; i < this->mapStates.size() ; i++) {
    delete this->mapStates[i];
  }

  for (size_t i = 0 ; i < this->shortCollection.size() ; i++) {
		delete this->shortCollection[i];
	}

  for (size_t i = 0 ; i < this->longCollection.size() ; i++) {
		delete this->longCollection[i];
	}

  std::map<std::size_t, std::vector<View::Worm*>>::iterator itMap = this->wormsCollection.begin();
	for (; itMap != this->wormsCollection.end() ; itMap++) {
		std::vector<View::Worm*>::iterator it = itMap->second.begin();
		for (; it != itMap->second.end() ; it++) {
			delete *it;
		}
	}
}

void View::MapGame::render(SDL_Renderer * renderer, int camX, int camY) {
  YAML::Node * state = this->mapStates[this->stateIndex];

  // Render short girders
  const YAML::Node & gs = (*state)["static"]["short_girders"];
  YAML::const_iterator it = gs.begin();
  for (; it != gs.end() ; it++) {
    const YAML::Node & eachGirder = *it;
    View::GirderShort g(renderer, eachGirder["angle"].as<int>());
    g.setX(eachGirder["x"].as<int>());
    g.setY(eachGirder["y"].as<int>());
    g.render(renderer, camX, camY);
  }

  // Render long girders
  const YAML::Node & gl = (*state)["static"]["long_girders"];
  it = gl.begin();
  for (; it != gl.end() ; it++) {
    const YAML::Node & eachGirder = *it;
    View::GirderLong g(renderer, eachGirder["angle"].as<int>());
    g.setX(eachGirder["x"].as<int>());
    g.setY(eachGirder["y"].as<int>());
    g.render(renderer, camX, camY);
  }

  // Render worms
  const YAML::Node & worms = (*state)["dynamic"]["worms"];
  it = worms.begin();
  for (; it != worms.end() ; it++) {
    const YAML::Node & eachWorm = *it;
    View::Worm worm(
      renderer,
      eachWorm["name"].as<std::string>(),
      eachWorm["team"].as<int>(),
      eachWorm["health"].as<int>()
    );
    worm.setX(eachWorm["x"].as<int>());
    worm.setY(eachWorm["y"].as<int>());
    worm.render(renderer, camX, camY);
  }
}


/* Add methods */
void View::MapGame::addShortGirder(degrees_t degrees, int x, int y) {
  // Actualizamos el indice
  this->updateIndex();
  
  // Referencia al ultimo estado del mapa
  YAML::Node * lastState = this->mapStates.back();

  // Creamos un nuevo estado
  this->mapStates.push_back(new YAML::Node);
  YAML::Node * newState = this->mapStates.back();

  // Copiamos el ultimo estado en el nuevo estado
  (*newState) = YAML::Clone(*lastState);

  // Creamos el nuevo nodo correspondiente
  // a la nueva viga
  YAML::Node newNode;
  newNode["id"] = (*newState)["static"]["short_girders"].size() + 1;
  newNode["x"] = x;
  newNode["y"] = y;
  newNode["angle"] = (int)degrees;

  // Agregamos el nuevo nodo 
  (*newState)["static"]["short_girders"].push_back(newNode);
}

void View::MapGame::addLongGirder(degrees_t degrees, int x, int y) {
  // Actualizamos el indice
  this->updateIndex();

  // Referencia al ultimo estado del mapa
  YAML::Node * lastState = this->mapStates.back();

  // Creamos un nuevo estado
  this->mapStates.push_back(new YAML::Node);
  YAML::Node * newState = this->mapStates.back();

  // Copiamos el ultimo estado en el nuevo estado
  (*newState) = YAML::Clone(*lastState);

  // Creamos el nuevo nodo correspondiente
  // a la nueva viga
  YAML::Node newNode;
  newNode["id"] = (*newState)["static"]["long_girders"].size() + 1;
  newNode["x"] = x;
  newNode["y"] = y;
  newNode["angle"] = (int)degrees;

  // Agregamos el nuevo nodo
  (*newState)["static"]["long_girders"].push_back(newNode);
}

void View::MapGame::addWormInTeam(int teamId, std::string & name, int health, int x, int y) {
  // Actualizamos el indice
  this->updateIndex();

  // Referencia al ultimo estado del mapa
  YAML::Node * lastState = this->mapStates.back();

  // Creamos un nuevo estado
  this->mapStates.push_back(new YAML::Node);
  YAML::Node * newState = this->mapStates.back();

  // Copiamos el ultimo estado en el nuevo estado
  (*newState) = YAML::Clone(*lastState);

  // Creamos el nuevo nodo correspondiente
  // al nuevo gusano
  YAML::Node newNode;
  newNode["id"] = this->getNextWormId(teamId);
  newNode["team"] = teamId;
  newNode["name"] = name;
  newNode["health"] = health;
  newNode["x"] = x;
  newNode["y"] = y;
  
  // Configuramos el status del gusano por default
  newNode["status"]["grounded"] = (int)false;
  newNode["status"]["falling"] = (int)true;
  newNode["status"]["mirrored"] = (int)false;
  newNode["status"]["walking"] = (int)false;


  // Agregamos el nuevo nodo
  (*newState)["dynamic"]["worms"].push_back(newNode);
}

void View::MapGame::setPreviousState(View::EditorInventory & inv) {
  if (this->stateIndex) {
    this->stateIndex--;
    YAML::Node * currentState = this->mapStates[this->stateIndex];
    const YAML::Node & wormsNode = (*currentState)["dynamic"]["worms"];
    inv.updateWormsTeamSupplies(wormsNode);
  }
}

void View::MapGame::setNextState(View::EditorInventory & inv) {
  if (this->stateIndex != this->mapStates.size() - 1) {
    this->stateIndex++;
    YAML::Node * currentState = this->mapStates[this->stateIndex];
    const YAML::Node & wormsNode = (*currentState)["dynamic"]["worms"];
    inv.updateWormsTeamSupplies(wormsNode);
  }
}

void View::MapGame::printCurrentState(void) {
  std::cout << *this->mapStates[this->stateIndex] << std::endl;
}

void View::MapGame::updateIndex(void) {
  this->stateIndex++;
  // Todavia no se agrego el nuevo nodo y el indice
  // se aumento, por eso comparamos contra size
  if (this->stateIndex != this->mapStates.size()) {
    std::vector<YAML::Node*>::iterator it = this->mapStates.begin() + this->stateIndex;
    for (; it != this->mapStates.end() ;) {
      delete *it;
      it = this->mapStates.erase(it);
    }
  }
}

int View::MapGame::getNextWormId(int teamId) {
  int id = 1;
  YAML::Node * state = this->mapStates[this->stateIndex];

  const YAML::Node & worms = (*state)["dynamic"]["worms"];
  YAML::const_iterator it = worms.begin();
  for (; it != worms.end() ; it++) {
    const YAML::Node & eachWorm = *it;
    if (teamId == eachWorm["team"].as<int>()) {
      id++;
    }
  }

  return id;
}