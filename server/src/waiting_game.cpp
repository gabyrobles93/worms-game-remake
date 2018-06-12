#include <string>
#include "waiting_game.h"
#include "client.h"
#include <unistd.h>
#include "server_game.h"

WaitingGame::WaitingGame(Client * cn, std::string & mn, size_t pq) {
    this->members.push_back(cn);
    this->match_name = mn;
    this->players_qty = pq;
    this->joined_players = 1;
    this->finished = false;
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
    size_t team_id = 1;
    for (it = this->members.begin(); it != this->members.end(); it++) {
        std::string tid = std::to_string(team_id);
        (*it)->setIdInMatch(team_id);
        (*it)->sendGameStart(1, msg, tid);
        team_id++;
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

void WaitingGame::startGame(std::string & map_path) {
    std::unique_lock<std::mutex> lock(this->mutex);
    std::cout << "Iniciando partida." << std::endl;
//    usleep(10000000);
    ServerGame new_server_game(members, map_path);
    new_server_game.startGame();
    this->finished = true;
    this->cv.notify_all();
    std::cout << "Partida finalizada" << std::endl;
}

bool WaitingGame::hasFinished(void) {
    return this->finished;
}

void WaitingGame::waitUntilFinish(void) {
    std::cout << "Esperando a que termine la partida." << std::endl;
    std::unique_lock<std::mutex> lock(this->mutex);
    while (!this->finished) {
        this->cv.wait(lock);
    }
    std::cout << "La partida termino, ya no esperaré mas." << std::endl;
}