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
        int winner_team;
        int turn_timeleft_sec;
        bool turn_finished;
        bool worms_moving;
        bool alive_projectiles;
        bool worms_affected_by_explosion;
        bool protagonic_worm_got_hurt;
        bool protagonic_worm_did_shoot;

        void createTeams(std::map<int, Worm*> &);
        int removeDeadTeamsTurns(void);
        void removeDeadWormsTurns(void);
        void refreshWormsFlagsByNewTurn(void);

    public:
        Match(std::map<int, Worm*> &, size_t);
        void printTeams(void);
        int getTeamTurn(void);
        int getWormTurn(int);
        void start(unsigned int);
        int nextTurn(void);
        void update(unsigned int);
        bool finished(void);
        int getWinner(void);
        int getTurnTimeleft(void);
        std::vector<size_t> getAliveTeams(void);
        void setAliveProjectilesFlag(bool);
        void setMovingWormsFlag(bool);
        void setWormsAffectedByExplosion(bool);
        void setProtagonicWormGotHurt(bool);
        void setProtagonicWormDidShoot(bool);
};

#endif