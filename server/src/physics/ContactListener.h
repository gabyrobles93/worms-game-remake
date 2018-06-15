#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include "Box2D.h"
#include "Entity.h"
#include "Girder.h"
#include "Worm.h"
#include "Bat.h"
#include "Bazooka.h"
#include "Missil.h"
#include "Fragment.h"
#include "Grenade.h"

class ContactListener : public b2ContactListener {
public: 
    ContactListener();
    virtual ~ContactListener();
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};

#endif