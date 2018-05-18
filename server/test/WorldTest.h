#ifndef _WORLD_TEST_H
#define _WORLD_TEST_H

#include <cxxtest/TestSuite.h>
#include "Worm.h"
#include "World.h"
#include "Girder.h"
#include <iostream>

class WorldTest : public CxxTest::TestSuite {
    public:
        void testAddition(void) {
            wormPositionTest();
            worldTest();
            //TS_ASSERT(1+1>1);
            //TS_ASSERT_EQUALS(1+1,2);
        }

        void wormPositionTest(void) {
            std::cout << "Test wormPosition" << std::endl;
            b2Vec2 gravity(0.0f, -10.0f);
            b2World world(gravity);
            Worm worm(1, world, 500.0f, 50.0f);
            TS_ASSERT(worm.getPosX() == 500.0f);
            TS_ASSERT(worm.getPosY() == 50.0f);
        }

        void worldTest(void) {
            std::cout << "Cargar girders en el mundo a partir de un archivo" << std::endl;
            World world;
            std::map<int,  Girder*> girders = world.getGirders();
            for (std::map<int, Girder*>::iterator it = girders.begin(); it!= girders.end(); ++it) {
                std::cout << it->first << " " << it->second->getPosX() << " " << it->second->getPosY() << std::endl;
            }
        }
};

#endif