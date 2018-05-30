#ifndef __MATCH_H__
#define __MATCH_H__

#include <map>
#include <vector>
#include <queue>
#include "team.h"
#include "Worm.h"
#include "thread.h"

class Match {
    private:
        std::map<int, Team *> teams;
        std::map<int, Worm *> & worms;
        std::queue<int> team_turn_order;
        std::map<int, std::queue<int>> worm_turn_order;
        unsigned int turn_duration_sec;
        unsigned int actual_turn_start_time;
        bool match_finished;

        void createTeams(std::map<int, Worm*> &);
        void removeDeadWormsTurns(void);

    public:
        Match(std::map<int, Worm*> &, size_t);
        void printTeams(void);
        int getTeamTurn(void);
        int getWormTurn(int);
        void start(unsigned int);
        int nextTurn(void);
        void update(unsigned int);
        bool finished(void);
};

#endif