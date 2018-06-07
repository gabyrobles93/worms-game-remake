#ifndef __PROTECTED_MATCHS_STATUS_H__
#define __PROTECTED_MATCHS_STATUS_H__

#include "yaml.h"
#include <mutex>

class ProtectedMatchsStatus {
    private:
        std::mutex mutex;
        YAML::Node matchs_status;
    public:
        ProtectedMatchsStatus(void);
        YAML::Node getMatchsStatus(void);
};

#endif