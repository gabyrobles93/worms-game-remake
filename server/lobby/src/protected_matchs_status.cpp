#include "protected_matchs_status.h"
#include "yaml.h"
#include <mutex>

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
    new_waiting_game["creator"] = waiting_game->getCreator();
    new_waiting_game["required_players"] = REQUIRED_PLAYERS;
    new_waiting_game["joined_players"] = 0;
    this->matchs_status["waiting_games"].push_back(new_waiting_game);
}