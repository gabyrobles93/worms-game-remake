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
    int actual_team_turn = getTeamTurn();
    this->team_turn_order.pop();
    if (this->teams[actual_team_turn]->haveAliveMember()) {
        this->team_turn_order.push(actual_team_turn);
    }

    if (this->team_turn_order.size() == 1) {
        //Partida con un ganador
        return -1;
    }

    if (this->team_turn_order.size() == 0) {
        // Partida sin ganadores
        return -2;
    }

    removeDeadWormsTurns();

    int worm_turn = getWormTurn(actual_team_turn);
    this->worm_turn_order[actual_team_turn].pop();
    if (!this->worms[worm_turn]->isDead()) {
        this->worm_turn_order[actual_team_turn].push(worm_turn);
    }    

    return 0;
}

void Match::removeDeadWormsTurns(void) {
    std::map<int, std::queue<int>>::iterator it;
    for (it = this->worm_turn_order.begin(); it != this->worm_turn_order.end(); it++) {
        size_t queue_size = it->second.size();
        while (queue_size > 0) {
            int worm_id = it->second.front();
            it->second.pop();
            if (!this->worms[worm_id]->isDead()) {
                it->second.push(worm_id);
            }
            queue_size--;
        }
    }
}

void Match::start(unsigned int actual_time_sec) {
    this->actual_turn_start_time = actual_time_sec;
}

void Match::update(unsigned int actual_time_sec) {
    if (actual_time_sec - this->actual_turn_start_time >= this->turn_duration_sec) {
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