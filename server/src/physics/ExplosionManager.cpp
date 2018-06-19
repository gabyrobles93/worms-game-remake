#include "ExplosionManager.h"

/*
Fuente: https://www.iforce2d.net/b2dtut/explosions
*/

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
        if ((bodyCom - center).Length() > radius)
            continue;
        this->applyBlastImpulse(body, center, bodyCom, power, radius);
    }
}

int ExplosionManager::calculateDamage(float blastPower, float radius, float distance) {
    return blastPower * ((-distance/radius) + 1);
}

void ExplosionManager::applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower, float radius) {
	b2Vec2 blastDir = applyPoint - blastCenter;
	float distance = blastDir.Normalize();
    int damage = this->calculateDamage(blastPower, radius, distance);
    if (blastDir.y > 0) blastDir.y = -blastDir.y;
	if (distance <= 1) distance = 1;
	float invDistance = 1/distance;
	float impulseMag = (blastPower/REDUCE_FACTOR) * invDistance;
    entity_t entity_type = static_cast<Entity*>(body->GetUserData())->getEntityType();
    if (entity_type == WORM) {
        body->ApplyLinearImpulse(impulseMag * blastDir, applyPoint, true);
        static_cast<Worm*>(body->GetUserData())->hurt(damage);
        static_cast<Worm*>(body->GetUserData())->setAffectedByExplosion();
    }
}


