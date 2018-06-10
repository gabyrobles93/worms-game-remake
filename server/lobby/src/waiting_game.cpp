#include <string>
#include "waiting_game.h"
#include "client.h"

WaitingGame::WaitingGame(Client * cn, std::string & mn, size_t pq) {
    this->members.push_back(cn);
    this->match_name = mn;
    this->players_qty = pq;
    this->joined_players = 1;
}

void WaitingGame::addPlayer(Client * new_member) {
    this->members.push_back(new_member);
    this->joined_players++;
}

std::string WaitingGame::getCreatorName(void) {
    return this->members.front()->getPlayerName();
}

std::string WaitingGame::getMatchName(void) {
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
    std::vector<Client *>::iterator it;
    for (it = this->members.begin(); it != this->members.end(); it++) {
        if ((*it)->getPlayerName() == player_name) {
            this->members.erase(it);
            this->joined_players--;
            return;
        }
    }
}

std::vector<std::string> WaitingGame::getWaitingPlayersName(void) {
    std::vector<std::string> players_names;
    std::vector<Client *>::iterator it;
    for (it = this->members.begin(); it != this->members.end(); it++) {
        players_names.push_back((*it)->getPlayerName());
    }    
    return players_names;
}

void WaitingGame::notifyAllStartGame(void) {
    std::vector<Client*>::iterator it;
    std::string msg = "started";
    for (it = this->members.begin(); it != this->members.end(); it++) {
        (*it)->sendResponse(1, msg);
    }
}

void WaitingGame::notifyAllCancellGame(void) {
    std::vector<Client*>::iterator it;
    std::string msg = "aborted";
    for (it = this->members.begin(); it != this->members.end(); it++) {
        if ((*it)->getPlayerName() == this->getCreatorName()) continue;
        (*it)->sendResponse(0, msg);
    } 
}