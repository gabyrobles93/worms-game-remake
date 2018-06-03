#include <iostream>
#include <unistd.h>
#include <map>
#include <vector>
#include <algorithm>
#include "team.h"
#include "match.h"

#define US_SEC_FACTOR 1000000

Match::Match(std::map<int, Worm*> & worms, size_t td) :
worms(worms) {
    this->turn_duration_sec = td;
    this->actual_turn_start_time = 0;
    this->match_finished = false;
    this->winner_team = -1;
    createTeams(worms);
}

void Match::createTeams(std::map<int, Worm*> & worms) {
    std::map<int, Worm *>::const_iterator it;
    for (it = worms.begin(); it != worms.end(); it++) {
        int team_id = it->second->getTeam();
        if (this->teams.find(team_id) == this->teams.end()) {
            Team * new_team = new Team(team_id);
            this->teams[team_id] = new_team;
            this->team_turn_order.push(team_id);
        }
        this->teams[team_id]->addMember(it->second);
        this->worm_turn_order[team_id].push(it->second->getId());
    }
}

void Match::printTeams(void) {
    std::map<int, Team *>::const_iterator it;
    for (it = this->teams.begin(); it != this->teams.end(); it++) {
        std::vector<int> worms_id = it->second->getWormsID();
        std::vector<int>::const_iterator it2;
        std::cout << "Equipo Número " << it->second->getTeamId() << std::endl;
        for (it2 = worms_id.begin(); it2 != worms_id.end(); it2++) {
            std::cout << "Integrante: " << *it2 << std::endl;
        }
    }
}

int Match::getTeamTurn(void) {
    return this->team_turn_order.front();
}

int Match::getWormTurn(int team_id) {
    return this->worm_turn_order[team_id].front();
}

int Match::nextTurn(void) {
    int alive_teams;
    int actual_team_turn = getTeamTurn();

    alive_teams = removeDeadTeamsTurns();
    if (alive_teams == 1) {
        this->winner_team = this->team_turn_order.front();
        //Partida con un ganador
        return -1;
    } else if (alive_teams == 0) {
        this->winner_team = 0;
        // Partida sin ganadores
        return -2;
    }

    if (this->team_turn_order.front() == actual_team_turn) {
        this->team_turn_order.pop();
        this->team_turn_order.push(actual_team_turn);
    }

    int actual_worm_turn = getWormTurn(actual_team_turn);
    removeDeadWormsTurns();

    if (this->worm_turn_order[actual_team_turn].front() == actual_worm_turn) {
        this->worm_turn_order[actual_team_turn].pop();
        this->worm_turn_order[actual_worm_turn].push(actual_team_turn);
    }

    cleanTeamStatusBeforeNewTurn();

    return 0;
}

void cleanTeamStatusBeforeNewTurn(void) {

}

int Match::removeDeadTeamsTurns(void) {
    int teams_qty = this->team_turn_order.size();
    for (int i = 0; i < teams_qty; i++) {
        int team_id = this->team_turn_order.front();
        this->team_turn_order.pop();
        if (this->teams[team_id]->haveAliveMember()) {
            this->team_turn_order.push(team_id);
        }
    }
    return this->team_turn_order.size();
}

void Match::removeDeadWormsTurns(void) {
    std::map<int, std::queue<int>>::iterator it;
    for (it = this->worm_turn_order.begin(); it != this->worm_turn_order.end(); it++) {
        int queue_size = it->second.size();
        for (int i = 0; i < queue_size; i++) {
            int worm_id = it->second.front();
            it->second.pop();
            if (!this->worms[worm_id]->isDead()) {
                it->second.push(worm_id);
            }
        }
    }
}

void Match::start(unsigned int actual_time_sec) {
    this->actual_turn_start_time = actual_time_sec;
}

void Match::update(unsigned int actual_time_sec) {
    if (actual_time_sec - this->actual_turn_start_time >= this->turn_duration_sec) {
        std::cout << "Se intentara cambiar de turno." << std::endl;
        if (nextTurn() < 0) {
            std::cout << "No se pudo cambiar de turno, la partida finalizó." << std::endl;
            this->match_finished = true;
        } else {
            std::cout << "Cambio de turno." << std::endl;
            this->actual_turn_start_time = actual_time_sec;
        }
    }
}

bool Match::finished(void) {
    return this->match_finished;
}

int Match::getWinner(void) {
    return this->winner_team;
}