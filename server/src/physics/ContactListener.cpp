#include "ContactListener.h"
#include <iostream>

ContactListener::ContactListener(){}
ContactListener::~ContactListener() {}


void ContactListener::BeginContact(b2Contact* contact) {
/*     void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
    void* fixtureBUserData = contact->GetFixtureB()->GetUserData(); */
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
   
    if (bodyAUserData && bodyBUserData) {
        entity_t entityA_type = static_cast<Entity*>(bodyAUserData)->getEntityType(); 
        entity_t entityB_type = static_cast<Entity*>(bodyBUserData)->getEntityType();    

        //WORM FOOT CONTACT
        if (entityA_type == WORM && entityB_type == STRUCTURE) {
            static_cast<Worm*>(bodyAUserData)->addFootContact();
        //     float ground_angle = static_cast<Girder*>(bodyBUserData)->getAngle();
        //     static_cast<Worm*>(bodyAUserData)->setAngle(ground_angle);
        }
        if (entityB_type == WORM && entityA_type == STRUCTURE) {
            static_cast<Worm*>(bodyBUserData)->addFootContact();
            // float ground_angle = static_cast<Girder*>(bodyAUserData)->getAngle();
            // static_cast<Worm*>(bodyBUserData)->setAngle(ground_angle);
        }

        //WORM WATER CONTACT
        // if (entityA_type == WORM && entityB_type == WATER) {
        //     static_cast<Worm*>(bodyAUserData)->die();
        // }
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
            static_cast<Worm*>(bodyAUserData)->deleteFootContact();
        }

        if (entityB_type == WORM && entityA_type == STRUCTURE) {
            static_cast<Worm*>(bodyBUserData)->deleteFootContact();
        }
    }
}