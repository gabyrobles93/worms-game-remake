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
