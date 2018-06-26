#include "Bat.h"
#include "types.h"

Bat::Bat(b2World& world, float posX, float posY, bool mirrored, float angle) :
world(world) {
    this->posX = posX;
    this->posY = posY;
    this->mirrored = mirrored;
    this->angle = angle;
    this->rayLength = gConfiguration.BAT_LENGTH;
    rayCast();
}

void Bat::rayCast() {
    float c_angle;
    if (mirrored) {
        c_angle = 90 - angle;
    } else c_angle = 270 + angle;

    c_angle = c_angle * gConfiguration.DEGTORAD;    
    b2Vec2 rayDir(sinf(c_angle), cosf(c_angle));
    b2Vec2 center(posX, posY);
    rayDir.y = -rayDir.y;    
    b2Vec2 p2 = center + rayLength * rayDir;
    RayCastClosestCallBack callback;

    this->world.RayCast(&callback, center, p2);
    if (callback.body) {
        entity_t entity_type = static_cast<Entity*>(callback.body->GetUserData())->getEntityType();
        if (entity_type == WORM) {   
            Worm * worm = static_cast<Worm*>(callback.body->GetUserData());         
            atack(worm, callback.body);
        }
    }

}

void Bat::atack(Worm* worm, b2Body* body) {
    float impulse = body->GetMass() * gConfiguration.BAT_IMPULSE;
    float x_impulse = impulse * cosf(angle * gConfiguration.DEGTORAD);
    float y_impulse = impulse * sinf(angle * gConfiguration.DEGTORAD);
    if (!mirrored) x_impulse = x_impulse * -1;
    body->ApplyLinearImpulse(b2Vec2(x_impulse, -y_impulse), body->GetWorldCenter(),true);
    worm->hurt(gConfiguration.BAT_DAMAGE);
    worm->setAffectedByExplosion();
}