#ifndef __EVENT_H__
#define __EVENT_H__

#include <iostream>
#include "types.h"
#include "yaml.h"
#include <string>

class Event {
    private:
        YAML::Node eventNode;
        action_t action;
        size_t team_id;
    public:
        Event(action_t action = a_noEvent , size_t team_id = 0);
        Event(action_t action, weapon_t, size_t);
        Event(YAML::Node &);
        bool quit(void);
        YAML::Node getNode(void);
        size_t getTeamId(void);
};

#endif