#include "map_game.h"

View::MapGame::MapGame(SDL_Renderer * r, YAML::Node & gameNode) {
  std::string backgroundPath = gameNode["background"][0]["file"].as<std::string>();
  std::cout << "Path backgrnd: " << backgroundPath << std::endl;
  const YAML::Node & nodeShortGirders = gameNode["short_girders"];
  const YAML::Node & nodeLongGirders = gameNode["long_girders"];
  
  YAML::const_iterator it;
  for (it = nodeShortGirders.begin() ; it != nodeShortGirders.end() ; it++) {
    const YAML::Node & eachGirder = *it;
    std::cout << "ID: " << eachGirder["id"].as<int>() << std::endl;
    std::cout << "Y: " << eachGirder["x"].as<int>() << std::endl;
    std::cout << "X: " << eachGirder["x"].as<int>() << std::endl;
    std::cout << "Angulesco: " << eachGirder["angle"].as<int>() << std::endl;
    std::cout << "END SHORT GIRDER - - -\n\n\n"; 	
  }

  for (it = nodeLongGirders.begin() ; it != nodeLongGirders.end() ; it++) {
    const YAML::Node & eachGirder = *it;
    std::cout << "ID: " << eachGirder["id"].as<int>() << std::endl;
    std::cout << "Y: " << eachGirder["x"].as<int>() << std::endl;
    std::cout << "X: " << eachGirder["x"].as<int>() << std::endl;
    std::cout << "Angulesco: " << eachGirder["angle"].as<int>() << std::endl;
    std::cout << "END LONG GIRDER - - -\n\n\n"; 	
  }
}

View::MapGame::~MapGame() {

}
