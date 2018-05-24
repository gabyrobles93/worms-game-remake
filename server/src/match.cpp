#include <iostream>
#include <unistd.h>
#include "team.h"
#include "match.h"

#define US_SEC_FACTOR 1000000

// [1]
Match::Match(std::map<int, Worm*> & worms, size_t rd) :
turns(createTeams(worms)) {
    this->keep_running = true;
    this->round_duration_sec = rd;
}

// Crea los equipos y devuelve la cantidad de quipos que creó
// Esto sirve para construir la clase turnos (ver constructor [1])
int Match::createTeams(std::map<int, Worm*> & worms) {
    std::map<int, Worm*>::const_iterator it;
    int team_qty = 0;
    for (it = worms.begin(); it != worms.end(); it++) {
        int team_id = it->second->getTeam();
        if (this->teams.find(team_id) == this->teams.end()) {
                Team * new_team = new Team(team_id);
                this->teams[team_id] = new_team;
                team_qty++;
        }
        this->teams[team_id]->addMember(it->second);
    }
    return team_qty;
}

Match::~Match(void) {
    std::map<int, Team*>::iterator it;
    for (it = this->teams.begin(); it != this->teams.end(); it++) {
        delete it->second;
    }   
}

void Match::printTeams(void) {
    std::map<int, Team*>::const_iterator it;
    for (it = this->teams.begin(); it != this->teams.end(); it++) {
        it->second->print();
    }   
}

bool Match::isTurnOf(int team_id) {
    return (this->turns.getTurn() == team_id ? true : false);
}

void Match::advanceTurn(void) {
    this->turns.finishTurn();
}

int Match::getTeamTurn(void) {
    return this->turns.getTurn();
}

bool Match::isRunning(void) const {
    return true;
}

size_t Match::getId(void) const {
    return 0;
}

void Match::run(void) {
    while (keep_running) {
        usleep(this->round_duration_sec * US_SEC_FACTOR);
        advanceTurn();
    }
}

void Match::stop(void) { 
    this->keep_running = false;
}