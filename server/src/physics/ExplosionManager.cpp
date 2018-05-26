#include "ExplosionManager.h"
#include <iostream>

ExplosionManager::ExplosionManager(b2World& world) :
world(world) {

}

void ExplosionManager::manageExplosion(b2Vec2 center, float radius, float power) {
    QueryCallback queryCallback;
    b2AABB aabb;
    aabb.lowerBound = center - b2Vec2(radius, radius);
    aabb.upperBound = center + b2Vec2(radius, radius);
    this->world.QueryAABB(&queryCallback, aabb);

    for (unsigned int i = 0; i < queryCallback.foundBodies.size(); i++) {
        b2Body* body = queryCallback.foundBodies[i];
        b2Vec2 bodyCom = body->GetWorldCenter();
        if ((bodyCom - center).Length() >= radius)
            continue;
        this->applyBlastImpulse(body, center, bodyCom, power);
    }
    
    // for(int i = 0; i < NUM_RAYS; i++) {
    //     float angle = (i / (float) NUM_RAYS) * 360 * GRADTORAD;
    //     b2Vec2 rayDir(sinf(angle), cosf(angle));
    //     b2Vec2 rayEnd = center + radius * rayDir;
    //     RayCastClosestCallBack callback;
    //     this->world.RayCast(&callback, center, rayEnd);
    //     if (callback.body) {
    //         this->applyBlastImpulse(callback.body, center, callback.point, (power));
    //     }
    // }
}

void ExplosionManager::applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower) {
	b2Vec2 blastDir = applyPoint - blastCenter;
	float distance = blastDir.Normalize();
	if (distance == 0)
		return;
	float invDistance = 1/distance;
	float impulseMag = blastPower * invDistance * invDistance / REDUCE_FACTOR;
    entity_t entity_type = static_cast<Entity*>(body->GetUserData())->getEntityType();
    if (entity_type == WORM) {
        body->ApplyLinearImpulse(impulseMag * blastDir, applyPoint, true);
        std::cout << "BLAST POWER " << blastPower<< std::endl;
        static_cast<Worm*>(body->GetUserData())->hurt((int) blastPower);
        std::cout << static_cast<Worm*>(body->GetUserData())->getName() << std::endl;
    }
	
}
