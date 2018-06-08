#ifndef __TEAM_H__
#define __TEAM_H__

#include <map>
#include <vector>
#include "Worm.h"
#include "yaml.h"

class Team {
    private:
        int team_id;
        int member_qty;
        std::map<int, Worm*>  worms;
        std::map<std::string, int> inventory;

    public:
        Team(int);
        ~Team(void);
        std::map<int, Worm*>  & getWorms();
        void addMember(Worm *);
        void initializeInventory(YAML::Node inventory_node);
        std::map<std::string, int> & getInventory();
        std::vector<int> getWormsID(void);
        void print(void) const;
        int getTeamId(void);
        bool haveAliveMember(void);
        int getTotalLife(void);
};

#endif
