#include "event.h"
#include <iostream>
#include <string>
#include <sstream>
#include "yaml.h"
#include "types.h"

Event::Event(action_t a, size_t tid) {
    this->action = a;
    this->eventNode["event"]["team_id"] = std::to_string(tid);
    this->eventNode["event"]["action"] = std::to_string(a);
}

Event::Event(action_t a, weapon_t w, size_t tid) {
    this->action = a;
    this->eventNode["event"]["team_id"] = std::to_string(tid);
    this->eventNode["event"]["action"] = std::to_string(a);
    this->eventNode["event"]["weapon"] = std::to_string(w);
}

Event::Event(YAML::Node & event) {
    this->eventNode = YAML::Clone(event);
    this->action = (action_t) event["event"]["action"].as<int>();
}

YAML::Node Event::getNode(void) {
    return this->eventNode;
}

bool Event::quit(void) {
    return this->action == a_quitGame ? true : false;
}
