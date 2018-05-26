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
        bool mirrored;
        WormPhysic wormPhysic;
        std::string name;
        b2World& world;

    public:
        // mirrored = true significa mirando a derecha
        Worm(std::string, bool mirrored, int id, int team_id, int h, b2World& World, float posX, float posY);
        virtual ~Worm(void);
        void hurt(int);
        void jump(void);
        void frontJump(void);
        void backJump(void);
        void moveLeft(void);
        void moveRight(void);
        float getPosY(void);
        float getPosX(void);
        int getId(void);
        int getTeam(void);
        int getHealth(void);
        std::string getName(void);
        entity_t getEntityType() {return WORM;}
        void addFootContact(void);
        void deleteFootContact(void);
        bool isMirrored(void);
        void setAngle(float angle);
        void shoot(entity_t weapon);
};

#endif
