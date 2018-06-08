#include <string>
#include "waiting_game.h"

WaitingGame::WaitingGame(std::string & cn, std::string & mn) {
    this->creator = cn;
    this->match_name = mn;
}

std::string const & WaitingGame::getCreator(void) {
    return this->creator;
}

std::string const & WaitingGame::getMatchName(void) {
    return this->match_name;
}