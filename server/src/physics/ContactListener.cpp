#include "ContactListener.h"
#include <iostream>

ContactListener::ContactListener(){}
ContactListener::~ContactListener() {}


void ContactListener::BeginContact(b2Contact* contact) {
    void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
    void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
   
    if (bodyAUserData && bodyBUserData) {
        std::cout << "SALDKFJASOEIJFASOIEJFASOEIJF" << std::endl;
        entity_t entityA_type = static_cast<Entity*>(bodyAUserData)->getEntityType(); 
        entity_t entityB_type = static_cast<Entity*>(bodyBUserData)->getEntityType();    

        std::cout << "ENTity A " << entityA_type << "ENTITY B" << entityB_type << std::endl;   

        //WORM FOOT CONTACT
        if (entityA_type == WORM && entityB_type == STRUCTURE) {
            static_cast<Worm*>(bodyAUserData)->addFootContact();
            std::cout << "GUSANO EN CONTACTO CON VIGA" << std::endl;
        }

        if (entityB_type == WORM && entityA_type == STRUCTURE) {
            static_cast<Worm*>(bodyBUserData)->addFootContact();
            std::cout << "GUSANO EN CONTACTO CON VIGA" << std::endl;
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