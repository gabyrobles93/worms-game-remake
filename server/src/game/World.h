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
#include "AirStrike.h"
#include "Wind.h"
#include "RedGrenade.h"
#include "Mortar.h"
#include "Bat.h"
#include "Teleportation.h"
#include "Wall.h"

#define GRADTORAD 0.0174533

class World : public Thread {
private:
    Queue<Snapshot*> & snapshots;
    bool keep_running;
    WorldPhysic worldPhysic;
    std::map<int, Girder *> girders;
    std::map<int, Worm *> worms;
    std::map<int, Weapon *> weapons;
    std::map<int, Team *> teams;
    int weapon_counter;
    Water * water;
    unsigned int time_sec;
    std::string & map_path;
    Wind* wind;
    WorldPhysic _createWorldPhysic();
    virtual bool isRunning(void) const;
    virtual size_t getId(void) const;
    void updateSnapshot();
    /* void updateWormsYAML(void); */
    /* void updateProjectilesYAML(void); */
    void updateBodies();
    /* void removeProjectileFromYAML(size_t); */

    // Dispara el arma dependiendo del evento
    // recibido del cliente
    void shootWeapon(Event &, size_t);
    YAML::Node map_node;

public:
    World(std::string &, Queue<Snapshot*> &);
    ~World(void);
    void initializeWorld();
    std::map<int, Worm *> & getWorms();
    std::map<int, Girder *> getGirders();
    std::map<int, Team*> & getTeams();
    Wind* getWind();
    virtual void run(void);
    /* YAML::Node getSnapshot(); */
    void stop();
    void executeAction(Event &, size_t);
    unsigned int getTimeSeconds(void);
    bool hasWormsMoving(void);
    bool hasAliveProjectiles(void);
    bool hasWormsAffectedByExplosion(void);
    bool hasWormGotHurt(size_t);
    bool hasWormShooted(size_t);

    void generateSnapshot();
};

#endif