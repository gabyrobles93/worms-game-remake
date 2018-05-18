#ifndef WORLD_H
#define WORLD_H

#include <map>
#include "WorldPhysic.h"
#include "Girder.h"
#include "Worm.h"
#include "yaml.h"

class World {
private:
    WorldPhysic worldPhysic;
    std::map<int, Girder*> girders;
    std::map<int, Worm*> worms;
public:
    World();
    void initializeWorld();

};

#endif