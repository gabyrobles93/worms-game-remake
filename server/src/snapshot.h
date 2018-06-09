#ifndef __SNAPSHOT_H__
#define __SNAPSHOT_H__

#include <map>
#include "Worm.h"
#include "yaml.h"
#include "match.h"
#include "Weapon.h"
#include "Configuration.h"

class Snapshot {
    private:
        YAML::Emitter snapshot;
    public:
        Snapshot();
        void updateTeams(std::map<int, Team*> & teams);
        void updateProjectiles(std::map<int, Weapon*> &);
        void updateGameStatus(Match &);
        const char* getSnapshot();     
};

#endif