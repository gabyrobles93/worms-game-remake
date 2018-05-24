#ifndef WORM_H
#define WORM_H

#include "WormPhysic.h"
#include "Box2D/Box2D.h"
#include <string>

class Worm {
    private:
        int health;
        int id;
        int team_id;
        float posX;
        float posY;
        WormPhysic wormPhysic;
        std::string name;

    public:
        Worm(std::string, int id, int team_id, int h, b2World& World, float posX, float posY);
        void jump();
        void jumpLeft();
        void jumpRight();
        void moveLeft();
        void moveRight();
        float getPosY();
        float getPosX();
        int getId();
        int getTeam();
        int getHealth();
        std::string getName();
};

#endif
