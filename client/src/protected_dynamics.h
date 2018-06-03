#ifndef __PROTECTED_DYNAMIC_MAP_H__
#define __PROTECTED_DYNAMIC_MAP_H__

#include <mutex>
#include "yaml.h"

class ProtectedDynamics {
    private:
        YAML::Node dynamics;
        std::mutex mutex;
    public:
        ProtectedDynamics(YAML::Node &);
        void update(YAML::Node &);
        YAML::Node getWorms(void);
        YAML::Node getProjectiles(void);
};

#endif