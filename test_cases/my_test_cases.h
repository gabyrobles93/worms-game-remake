#ifndef __MY_TEST_CASES_H__
#define __MY_TEST_CASES_H__

#include <cxxtest/TestSuite.h>

class MyTestSuite : public CxxTest::TestSuite {
    public:
        void testAddition(void) {
            TS_ASSERT(1+1>1);
            TS_ASSERT_EQUALS(1+1,2);
        }
};

#endif