#include <string>
#include <vector>
#include "snapshot.h"
#include "yaml.h"
#include "World.h"

Snapshot::Snapshot(YAML::Node mapNode) {
    this->statics = YAML::Clone(mapNode["static"]);
    YAML::Node dynamic_node;
    dynamic_node["dynamics"];
    this->dynamics = dynamic_node;
}

Snapshot::Snapshot() {
    //YAML::Node dynamic_node;
    //dynamic_node["dynamics"];
    //this->dynamics = dynamic_node;
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
    snapshot << YAML::BeginMap;
    snapshot << YAML::Key<< "worms_teams";
    snapshot << YAML::Value << YAML::BeginMap;

    std::map<int, Team*>::const_iterator teamss_it;
    for (teamss_it = teams.begin(); teamss_it != teams.end(); ++teamss_it) {
        
        int team_id = teamss_it->second->getTeamId();
        std::map<int, Worm*> & worms = teamss_it->second->getWorms();
        std::map<int, Worm*>::const_iterator worm_it;

        
        snapshot << YAML::Key << (int) team_id;
        snapshot << YAML::Value << YAML::BeginMap;
        snapshot << YAML::Key << "worms";
        snapshot << YAML::Value << YAML::BeginSeq;
        
        for (worm_it = worms.begin(); worm_it != worms.end(); ++worm_it) {
            Worm* worm = worm_it->second;
            snapshot << YAML::BeginMap;
            snapshot << YAML::Key << "id" << YAML::Value << worm->getId();
            snapshot << YAML::Key << "name" << YAML::Value << worm->getName();
            snapshot << YAML::Key << "health" << YAML::Value << worm->getHealth();
            snapshot << YAML::Key << "x" << YAML::Value << (int)(worm->getPosX() / gConfiguration.SCALING_FACTOR);
            snapshot << YAML::Key << "y" << YAML::Value << (int)(worm->getPosY() / gConfiguration.SCALING_FACTOR);
            snapshot << YAML::Key << "sight_angle" << YAML::Value << worm->getSightAngle();
            snapshot << YAML::Key << "status";
            snapshot << YAML::Value << YAML::BeginMap;
            snapshot << YAML::Key << "grounded" << YAML::Value << (int) worm->isGrounded();
            snapshot << YAML::Key << "falling" << YAML::Value << (int) worm->isFalling();
            snapshot << YAML::Key << "mirrored" << YAML::Value << (int) worm->isMirrored();
            snapshot << YAML::Key << "walking" << YAML::Value << (int) worm->isWalking();
            snapshot << YAML::EndMap;
            snapshot << YAML::EndMap;
        }
        snapshot << YAML::EndSeq;

        std::map<std::string, int> inventory = teamss_it->second->getInventory();
        std::map<std::string, int>::const_iterator inventory_it;

        snapshot << YAML::Key << "inventory";
        snapshot << YAML::Value << YAML::BeginMap;

    int weapon_type = 1;
    for (inventory_it = inventory.begin(); inventory_it != inventory.end(); ++inventory_it) {
        snapshot << YAML::Key << weapon_type;
        snapshot << YAML::Value <<YAML::BeginMap;
        snapshot << YAML::Key << "item_name" << YAML::Value << inventory_it->first;
        snapshot << YAML::Key << "supplies" << YAML::Value << inventory_it->second;
        snapshot << YAML::EndMap;
        weapon_type++;
    }
    snapshot << YAML::EndMap;
    snapshot << YAML::EndMap;
    }

    snapshot << YAML::EndMap;
}

void Snapshot::updateProjectiles(std::map<int, Weapon*> & weapons) {
    snapshot << YAML::Key << "projectiles";
    snapshot << YAML::Value << YAML::BeginSeq;

    for (std::map <int, Weapon*>::iterator it = weapons.begin(); it != weapons.end(); ++it) {
        Weapon* weapon = it->second;
        snapshot << YAML::BeginMap;
        snapshot << YAML::Key << "id" << YAML::Value << weapon->getId();
        snapshot << YAML::Key << "type" << YAML::Value << std::to_string(weapon->getType());        
        snapshot << YAML::Key << "x" << YAML::Value << (int) (weapon->getPosX() /  gConfiguration.SCALING_FACTOR);
        snapshot << YAML::Key << "y" << YAML::Value << (int) (weapon->getPosY() /  gConfiguration.SCALING_FACTOR);
        snapshot << YAML::Key << "countdown" << YAML::Value << weapon->getCountdown();
        snapshot << YAML::Key << "exploded" << YAML::Value << (int) weapon->hasExploded();
        snapshot << YAML::Key << "blast_radius" << YAML::Value << (int) (weapon->getBlastRadius() / gConfiguration.SCALING_FACTOR);
        snapshot << YAML::EndMap;
    }
    snapshot << YAML::EndSeq;
}

void Snapshot::updateGameStatus(Match & match) {
    snapshot << YAML::Key << "game_status";
    snapshot << YAML::Value << YAML::BeginMap;
    snapshot << YAML::Key << "teams_health" << YAML::Value << match.getTeamInfo();
    snapshot << YAML::Key << "protagonic_worm" << YAML::Value << match.getWormTurn(match.getTeamTurn());
    snapshot << YAML::Key << "turn_timeleft" << YAML::Value << std::to_string(match.getTurnTimeleft());
    snapshot << YAML::Key << "finished" << YAML::Value << std::to_string(match.finished());
    snapshot << YAML::EndMap;
}

const YAML::Node& Snapshot::getSnapshot() {
    return this->dynamics;
}

const char* Snapshot::getSnapshotCString() {
    return this->snapshot.c_str();
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