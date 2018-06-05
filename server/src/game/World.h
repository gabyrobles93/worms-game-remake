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
#include "blocking_queue.h"
#include "event.h"
#include "snapshot.h"
#include "Configuration.h"
#include "Grenade.h"

#define GRADTORAD 0.0174533

class World : public Thread {
private:
    Queue<Snapshot> & snapshots;
//    YAML::Node node_map;
    Snapshot game_snapshot;
    bool keep_running;
    WorldPhysic worldPhysic;
    std::map<int, Girder *> girders;
    std::map<int, Worm *> worms;
    std::map<int, Weapon *> weapons;
    int weapon_counter;
    Water * water;
    unsigned int time_sec;

    WorldPhysic _createWorldPhysic();
    virtual bool isRunning(void) const;
    virtual size_t getId(void) const;
    void updateSnapshot();
    /* void updateWormsYAML(void); */
    /* void updateProjectilesYAML(void); */
    void updateBodies();
    /* void removeProjectileFromYAML(size_t); */
    
public:
    World(std::string &, Queue<Snapshot> &);
    ~World(void);
    void initializeWorld();
    std::map<int, Worm *> & getWorms();
    std::map<int, Girder *> getGirders();
    virtual void run(void);
    /* YAML::Node getSnapshot(); */
    void stop();
    void executeAction(Event &, size_t);
    unsigned int getTimeSeconds(void);
    bool hasWormsMoving();
    bool hasAliveProjectiles();
    bool hasWormsAffectedByExplosion();
};

#endif