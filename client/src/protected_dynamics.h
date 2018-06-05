#ifndef __PROTECTED_DYNAMIC_MAP_H__
#define __PROTECTED_DYNAMIC_MAP_H__

#include <mutex>
#include "yaml.h"
#include <queue>

class ProtectedDynamics {
    private:
        std::queue<YAML::Node> models;
        YAML::Node dynamics;
    public:
        ProtectedDynamics(YAML::Node &);
        void addModel(YAML::Node &);
        YAML::Node getWorms(void);
        YAML::Node getProjectiles(void);
        int getTurnTimeLeft(void);
        size_t getWormProtagonicId(void);
        void popModel(void);
};

#endif