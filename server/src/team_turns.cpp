#include "team_turns.h"

TeamTurns::TeamTurns(int teams_qty) {
    for (int i = 1; i < teams_qty+1; i++) {
        this->team_turns.push(i);
    }
}

int TeamTurns::getTurn(void) {
    return this->team_turns.front();
}

void TeamTurns::finishTurn(void) {
    int turn = this->team_turns.front();
    this->team_turns.pop();
    this->team_turns.push(turn);
}