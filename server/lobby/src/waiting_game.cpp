#include <string>
#include "waiting_game.h"

WaitingGame::WaitingGame(std::string & cn, std::string & mn, size_t pq) {
    this->creator = cn;
    this->match_name = mn;
    this->players_qty = pq;
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