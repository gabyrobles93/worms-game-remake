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
        float angle;
        float sight_angle;
        float fallenDistance;

        bool affectedByExplosion;
        bool falled;        
        bool mirrored;
        bool falling;
        bool hurtInTurn;
        bool shootedInTurn;

        WormPhysic wormPhysic;
        std::string name;
        b2World& world;

    public:
        // mirrored = true significa mirando a derecha
        Worm(std::string, int id, int team_id, int h, b2World& World, float posX, float posY);
        virtual ~Worm(void);
        void hurt(int);
        void jump(void);
        void frontJump(void);
        void backJump(void);
        void moveLeft(void);
        void moveRight(void);
        void pointHigher(void);
        void pointMoreDown(void);
        float getPosY(void);
        float getPosX(void);
        void setPosY(float posY);
        void setPosX(float posX);
        void setAngle(float angle);
        int getId(void);
        int getTeam(void);
        int getHealth(void);
        float getSightAngle(void);
        std::string getName(void);
        entity_t getEntityType() {return WORM;}
        void addFootContact(void);
        void deleteFootContact(void);
        bool isMirrored(void);
        void shoot(/* entity_t weapon */);
        bool isWalking(void);
        bool isFalling(void);
        bool isGrounded(void);
        bool isDead(void);
        bool gotHurtInTurn(void);
        bool didShootInTurn(void);
        void setAffectedByExplosion();
        void setFalling(bool);
        void update(void);
        void kill(void);
        bool isMoving(void);
        bool isAffectedByExplosion(void);
        void refreshByNewTurn(void);
};

#endif
