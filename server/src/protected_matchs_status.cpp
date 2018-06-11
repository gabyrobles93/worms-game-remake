#include "protected_matchs_status.h"
#include "yaml.h"
#include <mutex>
#include <iostream>

#define REQUIRED_PLAYERS 3

ProtectedMatchsStatus::ProtectedMatchsStatus(void) {
//    this->matchs_status = YAML::LoadFile("../../games.yml");
}

YAML::Node ProtectedMatchsStatus::getMatchsStatus(void) {
    std::lock_guard<std::mutex> lck(this->mutex);
    return this->matchs_status;
}

void ProtectedMatchsStatus::addWaitingGame(WaitingGame * waiting_game) {
    std::lock_guard<std::mutex> lck(this->mutex);
    YAML::Node new_waiting_game;
    new_waiting_game["match_name"] = waiting_game->getMatchName();
    new_waiting_game["creator"] = waiting_game->getCreatorName();
    new_waiting_game["required_players"] = waiting_game->getPlayersQty();
    new_waiting_game["joined_players"] = 0;
    this->matchs_status["waiting_games"].push_back(new_waiting_game);
}

void ProtectedMatchsStatus::rmWaitingGame(std::string & creator_name) {
    std::lock_guard<std::mutex> lck(this->mutex);
    std::vector<YAML::Node> vectorized_games_node;
    std::vector<YAML::Node>::iterator it;
    vectorized_games_node = this->matchs_status["waiting_games"].as<std::vector<YAML::Node>>();
    for (it = vectorized_games_node.begin(); it != vectorized_games_node.end(); it++) {
        if ((*it)["creator"].as<std::string>() == creator_name) {
            vectorized_games_node.erase(it);
            break;
        }
    }
    this->matchs_status.reset();
    this->matchs_status["waiting_games"] = vectorized_games_node;
}