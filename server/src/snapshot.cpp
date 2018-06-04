#include <string>
#include "snapshot.h"
#include "yaml.h"
#include "World.h"

Snapshot::Snapshot(YAML::Node mapNode) {
    this->statics = YAML::Clone(mapNode["static"]);
    this->dynamics = YAML::Clone(mapNode["dynamic"]);
}

int Snapshot::getWaterLevel(void) {
    return this->statics["water_level"].as<int>();
}

YAML::Node Snapshot::getShortGirders(void) {
    return this->statics["short_girders"];
}

//CHEQUEAR QUE PASA SI NO HAY LONG GIRDERS EN EL MAPA, VER SI CRASHEA.
YAML::Node Snapshot::getLongGirders(void) {
    return this->statics["long_girders"];
}

YAML::Node Snapshot::getWormsTeams(void) {
    return this->dynamics["worms_teams"];
}

void Snapshot::updateWorms(std::map<int, Worm *> worms) {
    YAML::Node::iterator it;
    for (it = this->dynamics["worms_teams"].begin(); it != this->dynamics["worms_teams"].end(); it++) {
        YAML::Node worms_node = it->second["worms"];
        for (YAML::iterator worms_it = worms_node.begin(); worms_it != worms_node.end(); worms_it++) {
            YAML::Node worm = *worms_it;
            int id = worm["id"].as<int>();
            worm["x"] = std::to_string((int) (worms[id]->getPosX() / gConfiguration.SCALING_FACTOR));
            worm["y"] = std::to_string((int) (worms[id]->getPosY() / gConfiguration.SCALING_FACTOR));
            worm["sight_angle"] = std::to_string((int) worms[id]->getSightAngle());
            worm["health"] = std::to_string(worms[id]->getHealth());
            worm["status"]["mirrored"] = std::to_string(worms[id]->isMirrored());
            worm["status"]["walking"] = std::to_string(worms[id]->isWalking());
            worm["status"]["falling"] = std::to_string(worms[id]->isFalling());
            worm["status"]["grounded"] = std::to_string(worms[id]->isGrounded());
        }
    }
}

void Snapshot::updateProjectiles(std::map<int, Weapon*> weapons) {
    YAML::Node::iterator it;
    for (it = this->dynamics["projectiles"].begin(); it != this->dynamics["projectiles"].end(); it++) {
        YAML::Node projectile = *it;
        int weapon_id = projectile["id"].as<int>();
        projectile["x"] = std::to_string((int) (weapons[weapon_id]->getPosX() / gConfiguration.SCALING_FACTOR));
        projectile["y"] = std::to_string((int) (weapons[weapon_id]->getPosY() / gConfiguration.SCALING_FACTOR));
        projectile["countdown"] = std::to_string(weapons[weapon_id]->getCountdown());
        projectile["exploded"] = std::to_string(weapons[weapon_id]->hasExploded());
    }
}

void Snapshot::removeProjectile(size_t projectile_id) {
    std::vector<YAML::Node> vec_projectiles = this->dynamics["projectiles"].as<std::vector<YAML::Node>>();
    std::vector<YAML::Node>::iterator it;
    for (it = vec_projectiles.begin(); it != vec_projectiles.end(); it++) {
        if ((*it)["id"].as<size_t>() == projectile_id) {
            it = vec_projectiles.erase(it);
            break;
        }
    }
    
    this->dynamics["projectiles"].reset();
    this->dynamics["projectiles"] = vec_projectiles;
}

YAML::Node Snapshot::getSnapshot() {
    return this->dynamics;
}

void Snapshot::addProjectile(Weapon * projectile) {
    YAML::Node new_projectile;
    new_projectile["id"] = std::to_string(projectile->getId());
    // EL CLIENTE ESPERA UN STRING EJ "DYNAMITE". DESDE SERVER SOLO PODEMOS MANDAR EL WEAPON ID, ARI ARREGLATE XD
    new_projectile["type"] = std::to_string(projectile->getType());
    new_projectile["x"] = std::to_string((int) (projectile->getPosX() / gConfiguration.SCALING_FACTOR));
    new_projectile["y"] = std::to_string((int) (projectile->getPosY() / gConfiguration.SCALING_FACTOR));
    new_projectile["countdown"] = std::to_string(projectile->getCountdown());
    new_projectile["exploded"] = std::to_string(projectile->hasExploded());
    this->dynamics["projectiles"].push_back(new_projectile);
}

bool Snapshot::hasWeaponSupplies(size_t team_id, weapon_t weapon_type) {
    int supplies = this->dynamics["worms_teams"][team_id]["inventory"][(int)weapon_type]["supplies"].as<int>();
    std::cout << "El equipo " << team_id << " tiene " << supplies << " supplies del arma " << weapon_type << std::endl;
    if (supplies > 0) {
        return true;
    }
    return false;
}

void Snapshot::reduceWeaponSupply(size_t team_id , weapon_t weapon_type) {
    int supplies = this->dynamics["worms_teams"][team_id]["inventory"][(int)weapon_type]["supplies"].as<int>();
    this->dynamics["worms_teams"][team_id]["inventory"][(int)weapon_type]["supplies"] = std::to_string(--supplies);
}