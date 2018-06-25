#include "ContactListener.h"
#include <iostream>

ContactListener::ContactListener(){}
ContactListener::~ContactListener() {}

void ContactListener::BeginContact(b2Contact* contact) {

    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);

    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
   
    if (bodyAUserData && bodyBUserData) {
        entity_t entityA_type = static_cast<Entity*>(bodyAUserData)->getEntityType(); 
        entity_t entityB_type = static_cast<Entity*>(bodyBUserData)->getEntityType();    

        //WORM FOOT CONTACT
        if (entityA_type == WORM && entityB_type == STRUCTURE) {
            float angle = static_cast<Girder*>(bodyBUserData)->getAngle();
            static_cast<Worm*>(bodyAUserData)->setNormal(worldManifold.normal);
            if (angle <= 0.8 && angle >= -0.8) {
                static_cast<Worm*>(bodyAUserData)->setAngle(angle);
                static_cast<Worm*>(bodyAUserData)->addFootContact();
            }
        }

        if (entityB_type == WORM && entityA_type == STRUCTURE) {
            float angle = static_cast<Girder*>(bodyAUserData)->getAngle();
            static_cast<Worm*>(bodyBUserData)->setNormal(worldManifold.normal);
            if (angle <= 0.8 && angle >= -0.8) {
                static_cast<Worm*>(bodyBUserData)->setAngle(angle);
                static_cast<Worm*>(bodyBUserData)->addFootContact();
            }
        }

        //WORM WATER CONTACT
        if (entityA_type == WORM && entityB_type == WATER) {
           static_cast<Worm*>(bodyAUserData)->kill();
        }

        if (entityB_type == WORM && entityA_type == WATER) {
           static_cast<Worm*>(bodyBUserData)->kill();
        }

        //GRENADE WALL/WATER CONTACT
        if (entityA_type == GRENADE && (entityB_type == WALL || entityB_type == WATER)) {
            static_cast<Grenade*>(bodyAUserData)->explode();
        }

        if (entityB_type == GRENADE && (entityA_type == WALL || entityA_type == WATER)) {
            static_cast<Grenade*>(bodyBUserData)->explode();
        }

        //BAZOOKA WORM/STRUCTURE CONTACT
        if (entityA_type == BAZOOKA && (entityB_type == WORM || entityB_type == STRUCTURE || entityB_type == WATER)) {
            static_cast<Bazooka*>(bodyAUserData)->explode();
        }

        if (entityB_type == BAZOOKA && (entityA_type == WORM || entityA_type == STRUCTURE || entityA_type == WATER)) {
            static_cast<Bazooka*>(bodyBUserData)->explode();
        }

        //MISSIL STRUCTURE/WATER CONTACT
        if (entityA_type == MISSIL && (entityB_type == WORM || entityB_type == STRUCTURE || entityB_type == WATER || entityB_type == WALL)) {
            static_cast<Missil*>(bodyAUserData)->explode();
        }
        
        if (entityB_type == MISSIL && (entityA_type == WORM || entityA_type == STRUCTURE || entityA_type == WATER || entityB_type == WALL)) {
            static_cast<Missil*>(bodyBUserData)->explode();
        }

        // FRAGMENT STRUCTURE/WATER CONTACT
        if (entityA_type == FRAGMENT && (entityB_type == WORM || entityB_type == STRUCTURE || entityB_type == WATER)) {
            static_cast<Fragment*>(bodyAUserData)->explode();
        }
        
        if (entityB_type == FRAGMENT && (entityA_type == WORM || entityA_type == STRUCTURE || entityA_type == WATER)) {
            static_cast<Fragment*>(bodyBUserData)->explode();
        }
    }
}

void ContactListener::EndContact(b2Contact* contact) {
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

    if (bodyAUserData && bodyBUserData) {
        entity_t entityA_type = static_cast<Entity*>(bodyAUserData)->getEntityType(); 
        entity_t entityB_type = static_cast<Entity*>(bodyBUserData)->getEntityType();       

        //WORM FOOT CONTACT
        if (entityA_type == WORM && entityB_type == STRUCTURE) {
            float angle = static_cast<Girder*>(bodyBUserData)->getAngle();
            if (angle <= 0.8 && angle >= -0.8) {
                static_cast<Worm*>(bodyAUserData)->deleteFootContact();
                static_cast<Worm*>(bodyAUserData)->setNormal(b2Vec2(0,0));                    
            }
        }

        if (entityB_type == WORM && entityA_type == STRUCTURE) {
            float angle = static_cast<Girder*>(bodyAUserData)->getAngle();
            if (angle <= 0.8 && angle >= -0.8) {
                static_cast<Worm*>(bodyBUserData)->deleteFootContact();
                static_cast<Worm*>(bodyBUserData)->setNormal(b2Vec2(0,0));                    
            }
        }
    }
}