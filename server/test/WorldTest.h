#ifndef _WORLD_TEST_H
#define _WORLD_TEST_H

#include <cxxtest/TestSuite.h>
#include "Worm.h"
#include <iostream>

class WorldTest : public CxxTest::TestSuite {
    public:
        void testAddition(void) {
            wormPositionTest();
            //TS_ASSERT(1+1>1);
            //TS_ASSERT_EQUALS(1+1,2);
        }

        void wormPositionTest() {
            std::cout << "Test wormPosition" << std::endl;
            b2Vec2 gravity(0.0f, -10.0f);
            b2World world(gravity);
            Worm worm(1, world, 500.0f, 50.0f);
            TS_ASSERT(worm.getPosX() == 500.0f);
            TS_ASSERT(worm.getPosY() == 50.0f);
        }
};

#endif