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
        YAML::Node statics;
        YAML::Node dynamics;
    public:
        Snapshot(YAML::Node);
        int getWaterLevel(void);
        YAML::Node getShortGirders(void);
        YAML::Node getLongGirders(void);
        YAML::Node getWormsTeams(void);
        void updateWorms(std::map<int, Worm *>);
        void updateProjectiles(std::map<int, Weapon*>);
        void updateGameStatus(Match &);
        void removeProjectile(size_t);
        YAML::Node getSnapshot(void);
        void addProjectile(Weapon *);
        bool hasWeaponSupplies(size_t, weapon_t);
        void reduceWeaponSupply(size_t, weapon_t);      
};

#endif