#include "protected_waiting_games.h"
#include <mutex>
#include <map>
#include <string>
#include "waiting_game.h"
#include "yaml.h"

ProtectedWaitingGames::ProtectedWaitingGames(void) {

}

void ProtectedWaitingGames::addNewWaitingGame(std::string & creator_name, WaitingGame * new_waiting_game) {
    std::lock_guard<std::mutex> lck(this->mutex);
    this->waiting_games[creator_name] = new_waiting_game;
}

YAML::Node ProtectedWaitingGames::getGamesInfoNode(void) {
    std::lock_guard<std::mutex> lck(this->mutex);
    YAML::Node waiting_games;
    std::map<std::string, WaitingGame*>::const_iterator it;
    for (it = this->waiting_games.begin(); it != this->waiting_games.end(); it++) {
        YAML::Node a_waiting_game_node;
        a_waiting_game_node["match_name"] = it->second->getMatchName();
        a_waiting_game_node["creator"] = it->second->getCreatorName();
        a_waiting_game_node["required_players"] = it->second->getPlayersQty();
        a_waiting_game_node["joined_players"] = it->second->getJoinedPlayersQty();
        waiting_games["waiting_games"].push_back(a_waiting_game_node);
    }
    return waiting_games;
}

std::string ProtectedWaitingGames::getGameName(std::string & creator_name) {
    std::lock_guard<std::mutex> lck(this->mutex);
    return this->waiting_games[creator_name]->getMatchName();
}

void ProtectedWaitingGames::removeGame(std::string & creator_name) {
    std::lock_guard<std::mutex> lck(this->mutex);
    delete this->waiting_games[creator_name];
    this->waiting_games.erase(creator_name);
}

bool ProtectedWaitingGames::gameHasFreeSlots(std::string & creator_name) {
    std::lock_guard<std::mutex> lck(this->mutex);
    return this->waiting_games[creator_name]->hasFreeSlots();
}

void ProtectedWaitingGames::addPlayerToGame(std::string & creator_name, Client * new_player) {
    std::lock_guard<std::mutex> lck(this->mutex);
    this->waiting_games[creator_name]->addPlayer(new_player);
}

void ProtectedWaitingGames::rmvPlayerFromGame(std::string & creator_name, std::string & rm_player_name) {
    std::lock_guard<std::mutex> lck(this->mutex);
    this->waiting_games[creator_name]->rmPlayer(rm_player_name);
}

std::vector<std::string> ProtectedWaitingGames::getWaitingPlayers(std::string & creator_name) {
    std::lock_guard<std::mutex> lck(this->mutex);
    return this->waiting_games[creator_name]->getWaitingPlayersName();
}

void ProtectedWaitingGames::notifyAllStartGame(std::string & creator_name) {
    std::lock_guard<std::mutex> lck(this->mutex);
    this->waiting_games[creator_name]->notifyAllStartGame();
}

void ProtectedWaitingGames::notifyAllCancellGame(std::string & creator_name) {
    std::lock_guard<std::mutex> lck(this->mutex);
    this->waiting_games[creator_name]->notifyAllCancellGame();
}