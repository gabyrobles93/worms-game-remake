#include "event.h"
#include <iostream>
#include <string>
#include <sstream>
#include "yaml.h"
#include "types.h"

Event::Event(action_t a, size_t tid) {
    this->action = a;
    this->team_id = tid;
    this->eventNode["event"]["team_id"] = std::to_string(tid);
    this->eventNode["event"]["action"] = std::to_string(a);
}

Event::Event(action_t a, std::string & mn, size_t map_players_qty) {
    this->action = a;
    this->team_id = 0;
    this->eventNode["event"]["action"] = std::to_string(a);
    this->eventNode["event"]["match_name"] = mn;
    this->eventNode["event"]["map_players_qty"] = std::to_string(map_players_qty);
    this->eventNode["event"]["team_id"] = 0;
}

Event::Event(action_t a, std::string & mcn) {
    this->action = a;
    this->team_id = 0;
    this->eventNode["event"]["action"] = std::to_string(a);
    this->eventNode["event"]["creator_name"] = mcn;
    this->eventNode["event"]["team_id"] = 0;
}

Event::Event(action_t a, weapon_t w, size_t tid, int countdown, int power, int sight_angle) {
    this->action = a;
    this->team_id = tid;
    this->eventNode["event"]["team_id"] = std::to_string(tid);
    this->eventNode["event"]["action"] = std::to_string(a);
    this->eventNode["event"]["weapon"] = std::to_string(w);
    
    if (countdown != -1) {
        this->eventNode["event"]["countdown"] = std::to_string(countdown);
    }

    if (power != -1) {
        int powerConverted = (power / 150) + 10; // Hardcodeado 
        this->eventNode["event"]["power"] = std::to_string(powerConverted);
    }

    if (sight_angle != -1) {
        this->eventNode["event"]["sight_angle"] = std::to_string(sight_angle);
    } 
}

Event::Event(action_t a, weapon_t w, size_t tid, int remoteX, int remoteY) {
    this->action = a;
    this->team_id = tid;
    this->eventNode["event"]["team_id"] = std::to_string(tid);
    this->eventNode["event"]["action"] = std::to_string(a);
    this->eventNode["event"]["weapon"] = std::to_string(w);
    this->eventNode["event"]["remote_control_x"] = std::to_string(remoteX);
    this->eventNode["event"]["remote_control_y"] = std::to_string(remoteY);
}

Event::Event(YAML::Node & event) {
    this->eventNode = YAML::Clone(event);
    this->action = (action_t) event["event"]["action"].as<int>();
    this->team_id = event["event"]["team_id"].as<size_t>();
}

YAML::Node Event::getNode(void) {
    return this->eventNode;
}

bool Event::quit(void) {
    return (this->action == a_quitGame || this->action == a_quitLobby) ? true : false;
}

bool Event::createMatch(void) {
    return this->action == a_createMatch ? true : false;
}

size_t Event::getTeamId(void) {
    return this->team_id;
}