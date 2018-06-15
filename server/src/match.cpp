#include <iostream>
#include <unistd.h>
#include <map>
#include <vector>
#include <algorithm>
#include "team.h"
#include "match.h"

#define US_SEC_FACTOR 1000000

Match::Match(std::map<int, Worm*>& worms, std::map<int, Team*> & teams, Wind* wind, size_t td) :
teams(teams),
worms(worms),
wind(wind) {
    this->turn_duration_sec = td;
    this->actual_turn_start_time = 0;
    this->turn_timeleft_sec = td;
    this->match_finished = false;
    this->winner_team = -1;
    this->turn_finished = false;
    this->worms_moving = false;
    this->alive_projectiles = false;
    this->worms_affected_by_explosion = false;
    this->protagonic_worm_got_hurt = false;
    this->protagonic_worm_did_shoot = false;
    this->extra_time = false;
    createTeams();
}

void Match::createTeams() {
    std::map<int, Team*>::const_iterator it;
    for (it = this->teams.begin(); it != this->teams.end(); it++) {
        this->team_turn_order.push((it)->first);
        std::map<int, Worm*> worms_team = (it)->second->getWorms();
        std::map<int, Worm*>::const_iterator worms_it;
        
        for(worms_it = worms_team.begin(); worms_it != worms_team.end(); worms_it++) {
            this->worm_turn_order[(it)->second->getTeamId()].push(worms_it->second->getId());
        }

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
    this->wind->updateWindForce();
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
  
    int actual_worm_turn;
    if (getTeamTurn() == actual_team_turn) {
        actual_worm_turn = getWormTurn(actual_team_turn);
        removeDeadWormsTurns();
        if (getWormTurn(actual_team_turn) == actual_worm_turn) {
            this->worm_turn_order[actual_team_turn].pop();
            this->worm_turn_order[actual_team_turn].push(actual_worm_turn);
        }
        this->team_turn_order.pop();
        this->team_turn_order.push(actual_team_turn);
    }
    
    refreshWormsFlagsByNewTurn();

    return 0;
}

void Match::refreshWormsFlagsByNewTurn(void) {
    std::map<int, Worm *>::iterator it;
    for (it = this->worms.begin(); it != this->worms.end(); it++) {
        it->second->refreshByNewTurn();
    }
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

std::map<size_t, int> Match::getTeamInfo(void) {
    std::map<size_t, int> alive_teams;
    std::map<int, Team *>::const_iterator it;
    for (it = this->teams.begin(); it != this->teams.end(); it++) {
            alive_teams[it->second->getTeamId()] = it->second->getTotalLife();
    }
    return alive_teams;
}

void Match::start(unsigned int actual_time_sec) {
    this->actual_turn_start_time = actual_time_sec;
    std::cout << "Es el turno del equipo " << getTeamTurn() << " con su Worm " << getWormTurn(getTeamTurn()) << std::endl;
}

void Match::setMovingWormsFlag(bool flag) {
    this->worms_moving = flag;
}

void Match::setAliveProjectilesFlag(bool flag) {
    this->alive_projectiles = flag;
}

void Match::setWormsAffectedByExplosion(bool flag) {
    this->worms_affected_by_explosion = flag;
}

void Match::setProtagonicWormGotHurt(bool flag) {
    this->protagonic_worm_got_hurt = flag;
}

void Match::setProtagonicWormDidShoot(bool flag) {
    this->protagonic_worm_did_shoot = flag;
}

void Match::update(unsigned int time_passed) {
    //this->turn_timeleft_sec = this->turn_timeleft_sec - time_passed;
    if (this->match_finished) return;
    if (aliveTeams() < 2) {
        this->match_finished = true;
    }

    if (this->turn_timeleft_sec <= 0) {
        this->turn_finished = true;
        this->extra_time = false;
    } else {
        this->turn_timeleft_sec = this->turn_timeleft_sec - time_passed;
    }

    if (this->protagonic_worm_did_shoot && this->turn_timeleft_sec > 3) {
        this->turn_timeleft_sec = 3;
        this->protagonic_worm_did_shoot = false;
        this->extra_time = true;
    }

    if ((this->protagonic_worm_did_shoot || this->protagonic_worm_got_hurt) 
    && !this->worms_moving && !this->alive_projectiles && !this->worms_affected_by_explosion && this->turn_finished) {
        //this->extra_time = false;
        if (nextTurn() < 0) {
            std::cout << "No se pudo cambiar de turno, la partida finalizó." << std::endl;
            this->match_finished = true;
        } else {
            std::cout << "Es el turno del equipo " << getTeamTurn() << " con su Worm " << getWormTurn(getTeamTurn()) << std::endl;
            this->turn_timeleft_sec = this->turn_duration_sec;
            this->turn_finished = false;
            return;
        }        
    }    
}

int Match::getTurnTimeleft(void) {
    return this->turn_timeleft_sec;
}

bool Match::finished(void) {
    return this->match_finished;
}

int Match::getWinner(void) {
    return this->winner_team;
}

int Match::getTeamTotalLife(size_t team_id) {
    return this->teams[team_id]->getTotalLife();
}

int Match::getWindForce() {
    return this->wind->getWindForce();
}

bool Match::extraTime() {
    return this->extra_time;
}

void Match::removePlayer(size_t tid) {
    this->teams[(int)tid]->killAll();
    if (getTeamTurn() == tid) {
        if (nextTurn() < 0) {
            std::cout << "No se pudo cambiar de turno, la partida finalizó." << std::endl;
            this->match_finished = true;
        } else {
            std::cout << "Es el turno del equipo " << getTeamTurn() << " con su Worm " << getWormTurn(getTeamTurn()) << std::endl;
            this->turn_timeleft_sec = this->turn_duration_sec;
            this->turn_finished = false;
            return;
        }           
    }
}

size_t Match::aliveTeams(void) {
    size_t counter = 0;
    std::map<int, Team *>::const_iterator it;
    for (it = this->teams.begin(); it != this->teams.end(); it++) {
        if (it->second->haveAliveMember()) {
            counter++;
        }
    }
    return counter;
}
