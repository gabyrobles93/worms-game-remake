#include <map>
#include "team_turns.h"

TeamTurns::TeamTurns(int teams_qty, std::map<int, Team*> & teams) {
    for (int i = 1; i < teams_qty+1; i++) {
        this->team_turns.push(i);
    }

    std::map<int, Team*>::const_iterator it;
    for (int i = 1; i < teams_qty+1; i++) {
        std::vector<int> worms_ids = teams[i]->getWormsID();
        std::vector<int>::const_iterator it2;
        for (it2 = worms_ids.begin(); it2 != worms_ids.end(); it2++) {
            this->worms_turns[i].push(*it2);
        }
    }

}

int TeamTurns::getTeamTurn(void) {
    std::lock_guard<std::mutex> lck(this->mutex);
    return this->team_turns.front();
}

int TeamTurns::getWormTurn(int team_id) {
    std::lock_guard<std::mutex> lck(this->mutex);
    return this->worms_turns[team_id].front();
}

void TeamTurns::finishTurn(void) {
    int team_turn = getTeamTurn();
    int worm_turn = this->worms_turns[team_turn].front();
    std::lock_guard<std::mutex> lck(this->mutex);
    this->worms_turns[team_turn].pop();
    this->worms_turns[team_turn].push(worm_turn);
    this->team_turns.pop();
    this->team_turns.push(team_turn);
}