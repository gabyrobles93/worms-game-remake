#include <string>
#include "waiting_game.h"

WaitingGame::WaitingGame(std::string & cn, std::string & mn, size_t pq) {
    this->creator = cn;
    this->match_name = mn;
    this->players_qty = pq;
    this->joined_players = 1;
    this->members.push_back(cn);
}

void WaitingGame::addPlayer(std::string & new_member_name) {
    this->members.push_back(new_member_name);
    this->joined_players++;
}

std::string const & WaitingGame::getCreator(void) {
    return this->creator;
}

std::string const & WaitingGame::getMatchName(void) {
    return this->match_name;
}

size_t WaitingGame::getPlayersQty(void) {
    return this->players_qty;
}

bool WaitingGame::hasFreeSlots(void) {
    return (this->players_qty - this->joined_players) > 0;
}

size_t WaitingGame::getJoinedPlayersQty(void) {
    return this->joined_players;
}

void WaitingGame::rmPlayer(std::string & player_name) {
    std::vector<std::string>::iterator it;
    for (it = this->members.begin(); it != this->members.end(); it++) {
        if ((*it) == player_name) {
            this->members.erase(it);
            this->joined_players--;
            return;
        }
    }
}

std::vector<std::string> WaitingGame::getWaitingPlayers(void) {
    return members;
}