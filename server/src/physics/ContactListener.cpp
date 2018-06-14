#include "ContactListener.h"
#include <iostream>

ContactListener::ContactListener(){}
ContactListener::~ContactListener() {}

void ContactListener::BeginContact(b2Contact* contact) {

    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
   
    if (bodyAUserData && bodyBUserData) {
        entity_t entityA_type = static_cast<Entity*>(bodyAUserData)->getEntityType(); 
        entity_t entityB_type = static_cast<Entity*>(bodyBUserData)->getEntityType();    

        //WORM FOOT CONTACT
        if (entityA_type == WORM && entityB_type == STRUCTURE) {
            float angle = static_cast<Girder*>(bodyBUserData)->getAngle();
            if (angle <= 0.8 && angle >= -0.8) {
                static_cast<Worm*>(bodyAUserData)->setAngle(angle);
                static_cast<Worm*>(bodyAUserData)->addFootContact();
            }
        }

        if (entityB_type == WORM && entityA_type == STRUCTURE) {
            float angle = static_cast<Girder*>(bodyAUserData)->getAngle();
            if (angle <= 0.8 && angle >= -0.8) {
                static_cast<Worm*>(bodyBUserData)->setAngle(angle);
                static_cast<Worm*>(bodyBUserData)->addFootContact();
            }
        }

        //WORM WATER CONTACT
        if (entityA_type == WORM && entityB_type == WATER) {
           std::cout << "EL GUSANO " << static_cast<Worm*>(bodyAUserData)->getName() << " HA TOCADO EL AGUA" << std::endl;
           static_cast<Worm*>(bodyAUserData)->kill();
        }

        if (entityB_type == WORM && entityA_type == WATER) {
           std::cout << "EL GUSANO " << static_cast<Worm*>(bodyBUserData)->getName() << " HA TOCADO EL AGUA" << std::endl;
           static_cast<Worm*>(bodyBUserData)->kill();
        }

        //WORM BAT CONTACT
        if (entityA_type == BAT && entityB_type == WORM) {
            std::cout << "HUBO CONTACTO CON EL BATE" << std::endl;
            static_cast<Bat*>(bodyAUserData)->atack(static_cast<Worm*>(bodyBUserData));
        }

        if (entityB_type == BAT && entityA_type == WORM) {
            std::cout << "HUBO CONTACTO CON EL BATE" << std::endl;
            static_cast<Bat*>(bodyBUserData)->atack(static_cast<Worm*>(bodyAUserData));
        }

        //BAZOOKA WORM/STRUCTURE CONTACT
        if (entityA_type == BAZOOKA && (entityB_type == WORM || entityB_type == STRUCTURE || entityB_type == WATER)) {
            static_cast<Bazooka*>(bodyAUserData)->setContact(true);
        }

        if (entityB_type == BAZOOKA && (entityA_type == WORM || entityA_type == STRUCTURE || entityA_type == WATER)) {
            static_cast<Bazooka*>(bodyBUserData)->setContact(true);
        }

        //MISSIL STRUCTURE/WATER CONTACT
        if (entityA_type == MISSIL && (entityB_type == WORM || entityB_type == STRUCTURE || entityB_type == WATER)) {
            static_cast<Missil*>(bodyAUserData)->setContact(true);
        }
        
        if (entityB_type == MISSIL && (entityA_type == WORM || entityA_type == STRUCTURE || entityA_type == WATER)) {
            static_cast<Missil*>(bodyBUserData)->setContact(true);
        }

        // FRAGMENT STRUCTURE/WATER CONTACT
        if (entityA_type == FRAGMENT && (entityB_type == WORM || entityB_type == STRUCTURE || entityB_type == WATER)) {
            static_cast<Fragment*>(bodyAUserData)->setContact(true);
        }
        
        if (entityB_type == FRAGMENT && (entityA_type == WORM || entityA_type == STRUCTURE || entityA_type == WATER)) {
            static_cast<Fragment*>(bodyBUserData)->setContact(true);
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

        //BAZOOKA WORM/STRUCTURE CONTACT
        if (entityA_type == BAZOOKA && (entityB_type == WORM || entityB_type == STRUCTURE || entityB_type == WATER)) {
            static_cast<Bazooka*>(bodyAUserData)->setContact(false);
        }

        if (entityB_type == BAZOOKA && (entityA_type == WORM || entityA_type == STRUCTURE || entityA_type == WATER)) {
            static_cast<Bazooka*>(bodyBUserData)->setContact(false);
        }

        //MISSIL WORM/STRUCTURE CONTACT
        if (entityA_type == MISSIL && (entityB_type == WATER)) {
            static_cast<Missil*>(bodyAUserData)->setContact(false);
        }

        if (entityB_type == MISSIL && (entityA_type == WATER)) {
            static_cast<Missil*>(bodyBUserData)->setContact(false);
        }

    }
}