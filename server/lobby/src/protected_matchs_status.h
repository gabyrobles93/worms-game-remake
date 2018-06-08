#ifndef __PROTECTED_MATCHS_STATUS_H__
#define __PROTECTED_MATCHS_STATUS_H__

#include "yaml.h"
#include "waiting_game.h"
#include <mutex>
#include <string>

class ProtectedMatchsStatus {
    private:
        std::mutex mutex;
        YAML::Node matchs_status;
    public:
        ProtectedMatchsStatus(void);
        YAML::Node getMatchsStatus(void);
        void addWaitingGame(WaitingGame *);
        void rmWaitingGame(std::string &);
};

#endif