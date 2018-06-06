#ifndef __TEAM_H__
#define __TEAM_H__

#include <map>
#include <vector>
#include "Worm.h"

class Team {
    private:
        int team_id;
        int member_qty;
        std::map<int, Worm*> worms;

    public:
        Team(int);
        ~Team(void);
        void addMember(Worm *);
        std::vector<int> getWormsID(void);
        void print(void) const;
        int getTeamId(void);
        bool haveAliveMember(void);
        int getTotalLife(void);
};

#endif
