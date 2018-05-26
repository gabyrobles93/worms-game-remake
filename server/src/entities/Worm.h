#ifndef WORM_H
#define WORM_H


#include "WormPhysic.h"
#include "Box2D/Box2D.h"
#include "Entity.h"
#include <string>

class Worm : public Entity {
    private:
        int health;
        int id;
        int team_id;
        float posX;
        float posY;
        WormPhysic wormPhysic;
        std::string name;
        b2World& world;

    public:
        Worm(std::string, int id, int team_id, int h, b2World& World, float posX, float posY);
        void jump();
        void frontJump();
        void backJump();
        void moveLeft();
        void moveRight();
        float getPosY();
        float getPosX();
        int getId();
        int getTeam();
        int getHealth();
        std::string getName();
        entity_t getEntityType() {return WORM;}
        void addFootContact();
        void deleteFootContact();
        void setAngle(float angle);
        void shoot(entity_t weapon);
};

#endif
