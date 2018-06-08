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
        Snapshot();
        int getWaterLevel(void);
        YAML::Node getShortGirders(void);
        YAML::Node getLongGirders(void);
        YAML::Node getWormsTeams(void);
        YAML::Node getInventory(void);
        void updateTeams(std::map<int, Team*> & teams);
        void updateProjectiles(std::map<int, Weapon*> &);
        void updateGameStatus(Match &);
        void removeProjectile(size_t);
        const YAML::Node& getSnapshot(void);
        void addProjectile(Weapon *);
        bool hasWeaponSupplies(size_t, weapon_t);
        void reduceWeaponSupply(size_t, weapon_t);      
};

#endif