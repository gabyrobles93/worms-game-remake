#include "projectiles.h"

View::Projectiles::Projectiles(void) {

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
  YAML::const_iterator it = projNode.begin();
  for (; it != projNode.end() ; it++) {
    const YAML::Node & proj = *it;
    int projId = proj["id"].as<int>();

    if (this->projectiles.find(projId) == this->projectiles.end()) {
      this->createProjectil(
        r,
        projId,
        proj
      );
    }
    Projectil * viewProjectile = this->projectiles[projId];
    viewProjectile->setX(proj["x"].as<int>());
    viewProjectile->setY(proj["y"].as<int>());
    viewProjectile->setCountdown(proj["countdown"].as<int>());
    viewProjectile->setExplode((bool)proj["exploded"].as<int>());
    if (proj["angle_direction"]) {
      viewProjectile->setAngleDirection(proj["angle_direction"].as<int>());
    }
  }

  this->cleanProjectilesFinished();
}

void View::Projectiles::createProjectil(SDL_Renderer * r, int projId, const YAML::Node & proj) {
  int count = proj["countdown"].as<int>();
  weapon_t type = (weapon_t)proj["type"].as<int>();
  int ratio = proj["blast_radius"].as<int>();

  switch (type) {
    case w_dynamite:
      this->projectiles[projId] = new View::Dynamite(r, count, ratio);
      break;

    case w_green_grenade:
      this->projectiles[projId] = new View::GreenGrenade(r, count, ratio);
      break;

    case w_holy_grenade:
      this->projectiles[projId] = new View::HolyGrenade(r, count, ratio);
      break;

    case w_banana:
      this->projectiles[projId] = new View::Banana(r, count, ratio);
      break;

    case w_bazooka:
      this->projectiles[projId] = new View::Bazooka(r, ratio);
      break;

    case w_mortar:
      this->projectiles[projId] = new View::Bazooka(r, ratio, w_mortar);
      break;

    case w_air_strike:
      this->projectiles[projId] = new View::AirStrike(r, ratio);
      break;
    
    case w_cluster:
      this->projectiles[projId] = new View::Cluster(r, count, ratio);
      break;

    default:
      throw View::Exception("%s: %i", ERR_MSG_UNKNOWN_PROJECTIL_TYPE, w_dynamite);
  }
}

void View::Projectiles::cleanProjectilesFinished(void) {
  std::map<size_t, Projectil *>::iterator it = this->projectiles.begin();
  for (; it != this->projectiles.end() ;) {
    Projectil * current = it->second;
    if (current->hasFinished()) {
      delete it->second;
      it = this->projectiles.erase(it);
    } else {
      it++;
    }
  }
}

const View::Projectil * View::Projectiles::getProjectilProtagonic(void) {
  if (this->projectiles.size()) {
    std::map<size_t, View::Projectil*>::const_iterator it = this->projectiles.begin();
    return it->second;
  } else {
    return nullptr;
  }
}
