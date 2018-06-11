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
        std::string matchName;
    public:
        Event(action_t action = a_noEvent , size_t team_id = 0);
        Event(action_t, std::string &, size_t map_players_qty);
        Event(action_t, std::string &);
        // Las armas que no se pueden configurar 
        // el countdown y o la potencia tienen
        // como parametro por default -1
        Event(action_t action, weapon_t, size_t, int countdown = -1, int power = -1, int sight_angle = -1);
        
        Event(YAML::Node &);
        bool quit(void);
        bool createMatch(void);
        bool goToMatch(void);
        YAML::Node getNode(void);
        size_t getTeamId(void);
};

#endif