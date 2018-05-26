#ifndef WORLD_H
#define WORLD_H

#include <map>
#include "WorldPhysic.h"
#include "Girder.h"
#include "Worm.h"
#include "yaml.h"
#include "Water.h"
#include "thread.h"
#include "types.h"
#include "ContactListener.h"
#include <sstream>
#include <Dynamite.h>

#define SCALING_FACTOR 0.0416
#define GRADTORAD 0.0174533

class World : public Thread{
private:
    bool keep_running;
    WorldPhysic _createWorldPhysic();
    WorldPhysic worldPhysic;
    std::map<int, Girder*> girders;
    std::map<int, Worm*> worms;
    Water* water;
    YAML::Node node_map;
    virtual bool isRunning(void) const;
    virtual size_t getId(void) const;
    void updateYAML();
    
public:
    World(std::string &);
    ~World(void);
    void initializeWorld();
    std::map<int, Worm*> & getWorms();
    std::map<int, Girder*> getGirders();
    virtual void run(void);
    //std::string getModel();
    YAML::Node getSnapshot();
    void moveLeft(size_t worm_id);
    void moveRight(size_t worm_id);
    void stop();
    void executeAction(action_t action, int id);
};

#endif