#include "DynamitePhysic.h"

void applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower) {
	b2Vec2 blastDir = applyPoint - blastCenter;
	float distance = blastDir.Normalize();
	if (distance == 0)
		return;
	float invDistance = 1/distance;
	float impulseMag = blastPower * invDistance * invDistance;
	body->ApplyLinearImpulse(impulseMag * blastDir, applyPoint, true);
}

DynamitePhysic::DynamitePhysic(b2World& world, float posX, float posY) {
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

void explode() {
    // b2Vec2 center = this->body->GetPosition();
    // for(int i = 0; i < numRays; i++) {
    //     float angle = (i / (float) numRays) * 360 * DEGTORAD;
    //     b2Vec2 rayDir(sinf(angle), cosf(angle));
    //     b2Vec2 raydEnd = center + blastRadius * rayDir;
    //     RayCastClosesCallBack callback;
    //     this->world->RayCast(&callback, center, rayEnd);
    //     if (callback.m_body) 
    //         applyBlastImpulse(callback.m_body, center, callback.m_point, (m_blastPower / (float)numRays));
    // }
}

