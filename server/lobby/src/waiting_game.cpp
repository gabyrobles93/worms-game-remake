#include <string>
#include "waiting_game.h"

WaitingGame::WaitingGame(std::string & creator_name) {
    this->creator = creator_name;
}

std::string const & WaitingGame::getCreator(void) {
    return this->creator;
}