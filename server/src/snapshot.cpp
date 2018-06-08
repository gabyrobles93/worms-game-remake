#include <string>
#include <vector>
#include "snapshot.h"
#include "yaml.h"
#include "World.h"

Snapshot::Snapshot(YAML::Node mapNode) {
    std::cout << "HOLA AMIGACHO" << std::endl;
    this->statics = YAML::Clone(mapNode["static"]);
    YAML::Node dynamic_node;
    dynamic_node["dynamics"];
    this->dynamics = dynamic_node;
}

Snapshot::Snapshot() {
    YAML::Node dynamic_node;
    dynamic_node["dynamics"];
    this->dynamics = dynamic_node;
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

YAML::Node Snapshot::getInventory(void) {
    return this->statics["init_inventory"];
}



void Snapshot::updateTeams(std::map<int, Team*> & teams) {
    std::map<int, Team*>::const_iterator teams_it;
    for (teams_it = teams.begin(); teams_it != teams.end(); ++teams_it) {
        
        int team_id = teams_it->second->getTeamId();
        std::map<int, Worm*> & worms = teams_it->second->getWorms();
        std::map<int, Worm*>::const_iterator worm_it;

        this->dynamics["worms_teams"][team_id];
        
        for (worm_it = worms.begin(); worm_it != worms.end(); ++worm_it) {
            Worm* worm = worm_it->second;
            YAML::Node worm_node;
            worm_node["id"] = worm->getId();
            worm_node["name"] = worm->getName();
            worm_node["health"] = worm->getHealth();        
            worm_node["x"] = (int) (worm->getPosX() / gConfiguration.SCALING_FACTOR);
            worm_node["y"] = (int) (worm->getPosY() / gConfiguration.SCALING_FACTOR);
            worm_node["sight_angle"] = worm->getSightAngle();
            worm_node["status"]["grounded"] = (int) worm->isGrounded();        
            worm_node["status"]["falling"] = (int) worm->isFalling();        
            worm_node["status"]["mirrored"] = (int) worm->isMirrored();
            worm_node["status"]["walking"] = (int) worm->isWalking();
            this->dynamics["worms_teams"][team_id]["worms"].push_back(worm_node);
        }

        std::map<std::string, int> inventory = teams_it->second->getInventory();
        std::map<std::string, int>::const_iterator inventory_it;
        
        int weapon_type = 1;
        for (inventory_it = inventory.begin(); inventory_it != inventory.end(); ++inventory_it) {
            this->dynamics["worms_teams"][team_id]["inventory"][weapon_type]["item_name"] = inventory_it->first;
            this->dynamics["worms_teams"][team_id]["inventory"][weapon_type]["supplies"] = inventory_it->second;
            weapon_type++;
        }
    }

    // std::stringstream ss;
    // ss << this->dynamics << std::endl;
    // std::cout << ss.str() << std::endl;
    // this->dynamics["worms_teams"];
}

void Snapshot::updateProjectiles(std::map<int, Weapon*> & weapons) {
    for (std::map <int, Weapon*>::iterator it = weapons.begin(); it != weapons.end(); ++it) {
        Weapon* weapon = it->second;
        YAML::Node projectile_node;
        projectile_node["id"] = weapon->getId();
        projectile_node["type"] = std::to_string(weapon->getType());
        projectile_node["x"] = (int) (weapon->getPosX() /  gConfiguration.SCALING_FACTOR);
        projectile_node["y"] = (int) (weapon->getPosY() /  gConfiguration.SCALING_FACTOR);
        projectile_node["countdown"] =  weapon->getCountdown();
        projectile_node["exploded"] = (int) weapon->hasExploded();
        projectile_node["blast_radius"] = weapon->getBlastRadius();
        this->dynamics["projectiles"].push_back(projectile_node);
    }
}

void Snapshot::updateGameStatus(Match & match) {
/*     std::vector<size_t> alive_teams = match.getAliveTeams();
    std::vector<size_t>::const_iterator it;
    for (it = alive_teams.begin(); it != alive_teams.end(); it++) {
        this->dynamics["game_status"]["alive_teams"][*it]["total_life"] = match.getTeamTotalLife(*it);
    } */
    this->dynamics["game_status"]["teams_health"] = match.getTeamInfo();
    this->dynamics["game_status"]["protagonic_worm"] = match.getWormTurn(match.getTeamTurn());
    this->dynamics["game_status"]["turn_timeleft"] = std::to_string(match.getTurnTimeleft());
    this->dynamics["game_status"]["finished"] = std::to_string(match.finished());
}


const YAML::Node& Snapshot::getSnapshot() {
    return this->dynamics;
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