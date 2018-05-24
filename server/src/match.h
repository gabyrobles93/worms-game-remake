#ifndef __MATCH_H__
#define __MATCH_H__

#include <map>
#include "team.h"
#include "Worm.h"
#include "team_turns.h"
#include "thread.h"

class Match : public Thread {
    private:
        std::map<int, Team*> teams;
        TeamTurns turns;
        bool keep_running;
        size_t round_duration_sec;

        int createTeams(std::map<int, Worm*> &);
        virtual bool isRunning(void) const;
        virtual size_t getId(void) const;
        void advanceTurn(void);
    public:
        Match(std::map<int, Worm*> &, size_t);
        ~Match(void);
        virtual void run(void);
        void stop(void);
        void printTeams(void);
        bool isTurnOf(int);
        int getTeamTurn(void);
};

#endif