#ifndef __TURNS_H__
#define __TURNS_H__

#include <mutex>
#include <queue>
#include <map>
#include "team.h"

class TeamTurns {
    private:
        std::mutex mutex;
        std::queue<int> team_turns;
        std::map<int, std::queue<int>> worms_turns; 
    public:
        TeamTurns(int teams_qty, std::map<int, Team*> &);
        int getTeamTurn(void);
        int getWormTurn(int);
        void finishTurn(void);
};

#endif