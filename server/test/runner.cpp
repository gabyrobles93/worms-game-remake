/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_WorldTest_init = false;
#include "WorldTest.h"

static WorldTest suite_WorldTest;

static CxxTest::List Tests_WorldTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_WorldTest( "WorldTest.h", 7, "WorldTest", suite_WorldTest, Tests_WorldTest );

static class TestDescription_suite_WorldTest_testAddition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WorldTest_testAddition() : CxxTest::RealTestDescription( Tests_WorldTest, suiteDescription_WorldTest, 9, "testAddition" ) {}
 void runTest() { suite_WorldTest.testAddition(); }
} testDescription_suite_WorldTest_testAddition;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
