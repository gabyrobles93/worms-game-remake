#ifndef __TEAM_H__
#define __TEAM_H__

#include <map>
#include "Worm.h"

class Team {
    private:
        int team_id;
        std::map<int, Worm*> worms;

    public:
        Team(int);
        ~Team(void);
        void addMember(Worm *);
        void print(void) const;
};

#endif
