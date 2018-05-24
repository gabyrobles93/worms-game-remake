#include "event.h"
#include <iostream>
#include <string>
#include <sstream>
#include "types.h"

Event::Event(action_t a, size_t tid) :
action(a),
team_id(tid) {
}

std::ostream & operator<<(std::ostream & out, Event & event) {
    out << event.team_id;
    out << " ";
    out << event.action;
    return out;
}

bool Event::quit(void) {
    return this->action == a_quitGame ? true : false;
}

void Event::load(const std::string & input) {
    std::istringstream ss(input);
    std::string team_id;
    std::string action;
    char delimiter = ' ';
    std::getline(ss, team_id, delimiter);
    std::getline(ss, action, delimiter);

    this->action = (action_t) std::stoi(action);
    this->team_id = std::stoi(team_id);
}

void Event::print(void) {
    std::cout << "Team ID: " << this->team_id << std::endl;
    std::cout << "Action:  " << this->action << std::endl;
}

size_t Event::getTeamId(void) {
    return this->team_id;
}

action_t Event::getAction(void) {
    return this->action;
}