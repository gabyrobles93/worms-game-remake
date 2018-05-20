#ifndef WORLD_H
#define WORLD_H

#include <map>
#include "WorldPhysic.h"
#include "Girder.h"
#include "Worm.h"
#include "yaml.h"
#include "thread.h"
#include <sstream>

#define SCALING_FACTOR 0.0416
#define GRADTORAD 0.005555556

class World : public Thread{
private:
    bool keep_running;
    WorldPhysic _createWorldPhysic();
    WorldPhysic worldPhysic;
    std::map<int, Girder*> girders;
    std::map<int, Worm*> worms;
    YAML::Node dynamic_node;
    virtual bool isRunning(void) const;
    virtual size_t getId(void) const;
    void updateWorld();
    
public:
    World(YAML::Node& mapNode);
    ~World(void);
    void initializeWorld(YAML::Node& mapNode);
    std::map<int, Worm*> getWorms();
    std::map<int, Girder*> getGirders();
    virtual void run(void);
    std::string getModel();

    void moveLeft(size_t worm_id);
    void moveRight(size_t worm_id);
};

#endif