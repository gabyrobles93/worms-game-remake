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
        }
        if (entityB_type == WORM && entityA_type == STRUCTURE) {
            static_cast<Worm*>(bodyBUserData)->addFootContact();
        }

        //WORM WATER CONTACT
         if (entityA_type == WORM && entityB_type == WATER) {
            static_cast<Worm*>(bodyAUserData)->hurt(100);
            std::cout << static_cast<Worm*>(bodyAUserData)->getName() << "¿ESta Muerto?" << static_cast<Worm*>(bodyAUserData)->isDead() << std::endl;
         }

         if (entityB_type == WORM && entityA_type == WATER) {
            static_cast<Worm*>(bodyBUserData)->hurt(100);
            std::cout << static_cast<Worm*>(bodyBUserData)->getName() << "¿ESta Muerto?" << static_cast<Worm*>(bodyBUserData)->isDead() << std::endl;
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
            static_cast<Worm*>(bodyAUserData)->deleteFootContact();
        }

        if (entityB_type == WORM && entityA_type == STRUCTURE) {
            static_cast<Worm*>(bodyBUserData)->deleteFootContact();
        }
    }
}