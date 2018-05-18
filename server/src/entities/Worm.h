#ifndef WORM_H
#define WORM_H

#include "WormPhysic.h"
#include "Box2D/Box2D.h"

class Worm {
    private:
        int life;
        int id;
        float posX;
        float posY;
        WormPhysic wormPhysic;
    public:
        Worm(int id, b2World& World, float posX, float posY);
        void jump();
        void jumpLeft();
        void jumpRight();
        void moveLeft();
        void moveRight();
        float getPosY();
        float getPosX();
};

#endif