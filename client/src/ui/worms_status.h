#ifndef __WORMS_STATUS_H__
#define __WORMS_STATUS_H__

#include "yaml.h"

namespace View {
    class WormsStatus;
}

class View::WormsStatus {
    private:
        YAML::Node & dynamicMap;
    public:
        WormsStatus(YAML::Node &);
};

#endif