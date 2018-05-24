#ifndef __TURNS_H__
#define __TURNS_H__

#include <queue>

class TeamTurns {
    private:
        std::queue<int> team_turns;
    public:
        TeamTurns(int teams_qty = 0);
        int getTurn(void);
        void finishTurn(void);
};

#endif