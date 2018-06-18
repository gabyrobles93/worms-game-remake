#ifndef WORM_H
#define WORM_H

#include "Box2D/Box2D.h"
#include "Entity.h"
#include <string>
#include "PhysicEntity.h"
#include "Configuration.h"
#include "types.h"

#define WORM_HEIGHT 0.8f
#define WORM_RADIUS 0.54f
#define WORM_WIDTH 0.8f
#define WORM_DENSITY 1.0f
#define WORM_FRICTION 0.3f

class Worm : public Entity {
    private:
        int health;
        int id;
        int team_id;

        float posX;
        float posY;
        float angle;
        float fallenDistance;
        worm_inclination_t inclination;
        weapon_t weapon;

        bool affectedByExplosion;
        bool falled;        
        bool mirrored;
        bool falling;
        bool hurtInTurn;
        bool shootedInTurn;
        int numFootContacts;
        float normalX;
        float normalY;
        int direction_angle;
        std::string name;
        b2World& world;
        b2Body* body;
    public:
        // mirrored = true significa mirando a derecha
        Worm(std::string, int id, int team_id, int h, b2World& World, float posX, float posY);
        virtual ~Worm(void);
        void hurt(int);
        void frontJump(void);
        void backJump(void);
        void moveLeft(void);
        void moveRight(void);
        void pointHigher(void);
        void pointMoreDown(void);
        float getPosY(void);
        float getPosX(void);
        void setAngle(float angle);
        int getId(void);
        int getTeam(void);
        int getHealth(void);
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
        void setPosition(float posX, float posY);
        void setNormal(b2Vec2 normal);
        worm_inclination_t getInclination();
        int getDirectionAngle();
        void equipWeapon(weapon_t weapon);
};

#endif
