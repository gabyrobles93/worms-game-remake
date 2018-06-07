#include "protected_matchs_status.h"
#include "yaml.h"
#include <mutex>

ProtectedMatchsStatus::ProtectedMatchsStatus(void) {
//    this->matchs_status = YAML::LoadFile("../../games.yml");
}

YAML::Node ProtectedMatchsStatus::getMatchsStatus(void) {
    std::lock_guard<std::mutex> lck(this->mutex);
    return this->matchs_status;
}