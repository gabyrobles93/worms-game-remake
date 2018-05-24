#ifndef __EVENT_H__
#define __EVENT_H__

#include <iostream>
#include "types.h"
#include <string>

class Event {
    private:
        action_t action;
        size_t team_id;
    public:
        Event(action_t action = a_noEvent , size_t team_id = 0);
        friend std::ostream& operator<<(std::ostream &, Event &);
        bool quit(void);
        void load(const std::string & input);
        void print(void);
        size_t getTeamId(void);
        action_t getAction(void);
};

std::ostream& operator<<(std::ostream &, Event &);

#endif