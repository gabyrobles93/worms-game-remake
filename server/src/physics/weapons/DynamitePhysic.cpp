#include "DynamitePhysic.h"
#include <iostream>

// void DynamitePhysic::applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower) {
// 	b2Vec2 blastDir = applyPoint - blastCenter;
// 	float distance = blastDir.Normalize();
// 	if (distance == 0)
// 		return;
// 	float invDistance = 1/distance;
// 	float impulseMag = blastPower * invDistance * invDistance;
//     std::cout << static_cast<Worm*>(body->GetUserData())->getName() << std::endl;
// 	body->ApplyLinearImpulse(impulseMag * blastDir, applyPoint, true);
//     std::cout << "IMPULSO APLICADO" << std::endl;
// }

DynamitePhysic::DynamitePhysic(b2World& world, float posX, float posY) : world(world){
    b2BodyDef dynamiteDef;
    dynamiteDef.type = b2_dynamicBody;
    dynamiteDef.fixedRotation = true;
    dynamiteDef.position.Set(posX, posY);
    b2Body* body = world.CreateBody(&dynamiteDef);

    b2PolygonShape dynamiteShape;
    dynamiteShape.SetAsBox(0.1f, 0.2f);

    b2FixtureDef dynamiteFixture;
    dynamiteFixture.shape = &dynamiteShape;
    dynamiteFixture.density = 1;
    dynamiteFixture.friction = 1;
    body->CreateFixture(&dynamiteFixture);
    this->body = body;
}

DynamitePhysic::~DynamitePhysic() {
    this->world.DestroyBody(this->body);
}

void DynamitePhysic::explode() {
    ExplosionManager explosionManager(this->world);
    std::cout << "LA DINAMITA VA A EXPLOTAR" << std::endl;
    b2Vec2 center = this->body->GetPosition();
    explosionManager.manageExplosion(center, BLAST_RADIUS, BLAST_POWER);    
    // for(int i = 0; i < NUM_RAYS; i++) {
    //     float angle = (i / (float) NUM_RAYS) * 360 * GRADTORAD;
    //     b2Vec2 rayDir(sinf(angle), cosf(angle));
    //     b2Vec2 rayEnd = center + BLAST_RADIUS * rayDir;
    //     RayCastClosestCallBack callback;
    //     this->world.RayCast(&callback, center, rayEnd);
    //     if (callback.body) {
    //         std::cout << "CUERPO ENCONTRADO" << std::endl;
    //         this->applyBlastImpulse(callback.body, center, callback.point, (BLAST_POWER / (float)NUM_RAYS));
    //     }
    // }
}

