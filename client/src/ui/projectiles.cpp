#include "projectiles.h"

View::Projectiles::Projectiles(void) {
  this->projectilesTypes[WEAPON_NAME_BAZOOKA] = BAZOOKA;
  this->projectilesTypes[WEAPON_NAME_MORTAR] = MORTAR;
  this->projectilesTypes[WEAPON_NAME_GREEN_GRENADE] = GREEN_GRENADE;
  this->projectilesTypes[WEAPON_NAME_RED_GRENADE] = RED_GRENADE;
  this->projectilesTypes[WEAPON_NAME_BANANA] = BANANA;
  this->projectilesTypes[WEAPON_NAME_HOLY_GRENADE] = HOLY_GRENADE;
  this->projectilesTypes[WEAPON_NAME_DYNAMITE] = DYNAMITE;
  this->projectilesTypes[WEAPON_NAME_AIR_STRIKE] = AIR_STRIKE;
}

View::Projectiles::~Projectiles(void) {
  std::map<size_t, Projectil *>::iterator it = this->projectiles.begin();
  for (; it != this->projectiles.end() ; it++) {
    delete it->second;
  }
}

void View::Projectiles::render(SDL_Renderer * r, Camera & cam) {
  std::map<size_t, Projectil *>::iterator it = this->projectiles.begin();
  for (; it != this->projectiles.end() ; it++) {
    Projectil * current = it->second;
    if (!current->hasFinished()) {
      current->render(r, cam.getX(), cam.getY());
    }
  }
}

void View::Projectiles::update(SDL_Renderer * r, const YAML::Node & projNode) {
  std::cout << "PROJECTILES A UPDATEAR: " << std::endl;
  std::cout << projNode << std::endl;

  YAML::const_iterator it = projNode.begin();
  for (; it != projNode.end() ; it++) {
    const YAML::Node & proj = *it;
    int projId = proj["id"].as<int>();

    // Vemos si ya existe el proyectil
    if (this->projectiles.find(projId) != this->projectiles.end()) {
      Projectil * viewProjectile = this->projectiles[projId];
      viewProjectile->setX(proj["x"].as<int>());
      viewProjectile->setY(proj["y"].as<int>());
      viewProjectile->setCountdown(proj["countdown"].as<int>());
      viewProjectile->setExplode((bool)proj["exploded"].as<int>());
    } else {
      std::cout << "No existe el proyectil, lo creare\n";
      this->createProjectil(
        r, 
        projId, 
        proj["type"].as<std::string>(),
        proj["countdown"].as<int>()
      );
    }
  }

  this->cleanProjectilesFinished();
}

void View::Projectiles::createProjectil(SDL_Renderer * r, int projId, std::string name, int count) {
  projectil_t type = this->projectilesTypes[name];
  switch (type) {
    case DYNAMITE:
      this->projectiles[projId] = new View::Dynamite(r, count);
      break;
    default:
      throw View::Exception("%s: %s", ERR_MSG_UNKNOWN_PROJECTIL_TYPE, name);
  }
}

void View::Projectiles::cleanProjectilesFinished(void) {
  std::map<size_t, Projectil *>::iterator it = this->projectiles.begin();
  for (; it != this->projectiles.end() ; it++) {
    Projectil * current = it->second;
    if (current->hasFinished()) {
      delete it->second;
      it = this->projectiles.erase(it);
    }
  }
}