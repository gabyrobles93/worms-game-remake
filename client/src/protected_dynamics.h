#ifndef __PROTECTED_DYNAMIC_MAP_H__
#define __PROTECTED_DYNAMIC_MAP_H__

#include <mutex>
#include "yaml.h"
#include <queue>

class ProtectedDynamics {
    private:
        std::mutex mutex;
        std::queue<YAML::Node> models;
        YAML::Node dynamics;
    public:
        ProtectedDynamics(YAML::Node &);
        void addModel(YAML::Node &);
        YAML::Node getWorms(void);
        YAML::Node getProjectiles(void);
        YAML::Node getGameStatus(void);
        YAML::Node getTeamInventory(void);
        int getTurnTimeLeft(void);
        size_t getWormProtagonicId(void);
        bool popModel(void);
        bool hasGameStatus(void);
        size_t getTeamTurn(void);
};

#endif