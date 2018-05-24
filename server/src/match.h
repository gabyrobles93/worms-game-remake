#ifndef __MATCH_H__
#define __MATCH_H__

#include <map>
#include "team.h"
#include "Worm.h"
#include "team_turns.h"

class Match {
    private:
        std::map<int, Team*> teams;
        TeamTurns turns;
        int createTeams(std::map<int, Worm*> &);
    public:
        Match(std::map<int, Worm*> &);
        ~Match(void);
        void printTeams(void);
        bool isTurnOf(int);
        void advanceTurn(void);
        int getTeamTurn(void);
};

#endif