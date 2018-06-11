#include "Bat.h"
#include "types.h"
#include <iostream>

Bat::Bat(b2World& world, float posX, float posY, bool mirrored, float angle) :
world(world) {
    float rayLenth = 1;
    float c_angle;
    if (mirrored) c_angle = 90 - angle;
    if (!mirrored) c_angle = 270 + angle;
    // if (!mirrored && angle >= 0 && angle <= 90) {
    //     c_angle = 270 + angle;
    // } else if (!mirrored && angle < 0 && angle >= -90) {
    //     c_angle = 270 + angle;
    // } else if (mirrored && angle < 0 && angle >= -90) {
    //     c_angle = 90 - angle;
    // } else if (mirrored && angle >= 0 && angle <= 90) {
    //     c_angle = 90 - angle;
    // }
    c_angle = c_angle * gConfiguration.DEGTORAD;    
    b2Vec2 rayDir(sinf(c_angle), cosf(c_angle));
    b2Vec2 center(posX, posY);
    //b2Vec2 rayDir(sinf(cast_angle), cosf(cast_angle));
    //b2Vec2 p2;
    rayDir.y = -rayDir.y;    
    b2Vec2 p2 = center + rayLenth * rayDir;
    //= center + rayLenth * rayDir;
    //std::cout << "ANGULO " << angle << " SINF(ANGLE) : " << sinf(cast_angle) << "COSF(ANGLE) " << cosf(cast_angle) << std::endl; 
    std::cout << "PUNTO 1 " << center.x << ", " << center.y << std::endl;
    std::cout << "PUNTO 2 " << p2.x << ", " << p2.y << std::endl;
    RayCastClosestCallBack callback;

    // float angle = angle;
    // b2Vec2 rayDir = (sinf(angle), cosf(angle));
    // b2Vec2 rayEnd = center * rayDir;


    this->world.RayCast(&callback, center, p2);
    if (callback.body) {
        entity_t entity_type = static_cast<Entity*>(callback.body->GetUserData())->getEntityType();
        std::cout << "Entidad" << entity_type << std::endl;
        if (entity_type == WORM) {

            float impulse = callback.body->GetMass() * 10;
            float x_impulse = impulse * cosf(angle * gConfiguration.DEGTORAD);
            float y_impulse = impulse * sinf(angle * gConfiguration.DEGTORAD);
            if (!mirrored) x_impulse = x_impulse * -1;
            callback.body->ApplyLinearImpulse(b2Vec2(x_impulse, -y_impulse), callback.body->GetWorldCenter(),true);
            atack(static_cast<Worm*>(callback.body->GetUserData()));
        }
    }
}

void Bat::atack(Worm* worm) {
    worm->hurt(gConfiguration.BAT_DAMAGE);
}