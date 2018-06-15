#ifndef __MATCH_H__
#define __MATCH_H__

#include <map>
#include <vector>
#include <queue>
#include "team.h"
#include "Worm.h"
#include "thread.h"
#include "Wind.h"

class Match {
    private:
        std::map<int, Team *> & teams;
        std::map<int, Worm *> & worms;
        Wind* wind;
        std::queue<int> team_turn_order;
        std::map<int, std::queue<int>> worm_turn_order;
        unsigned int turn_duration_sec;
        unsigned int actual_turn_start_time;
        bool match_finished;
        int winner_team;
        int turn_timeleft_sec;
        bool turn_finished;
        bool worms_moving;
        bool alive_projectiles;
        bool worms_affected_by_explosion;
        bool protagonic_worm_got_hurt;
        bool protagonic_worm_did_shoot;
        bool extra_time;

        void createTeams();
        int removeDeadTeamsTurns(void);
        void removeDeadWormsTurns(void);
        void refreshWormsFlagsByNewTurn(void);

    public:
        Match(std::map<int, Worm*>& worms, std::map<int, Team*> &,Wind* wind, size_t);
        void printTeams(void);
        int getTeamTurn(void);
        int getWormTurn(int);
        void start(unsigned int);
        int nextTurn(void);
        void update(unsigned int);
        bool finished(void);
        int getWinner(void);
        int getTurnTimeleft(void);
        std::map<size_t, int> getTeamInfo(void);
        void setAliveProjectilesFlag(bool);
        void setMovingWormsFlag(bool);
        void setWormsAffectedByExplosion(bool);
        void setProtagonicWormGotHurt(bool);
        void setProtagonicWormDidShoot(bool);
        int getTeamTotalLife(size_t);
        int getWindForce();
        bool extraTime();
};

#endif