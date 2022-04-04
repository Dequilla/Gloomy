#ifndef __GLMY_TEST_MAIN_H__
#define __GLMY_TEST_MAIN_H__

#include <stdio.h>

#include <test/test_hashmap.h>
#include <test/test_utility.h>

int GLMY_TestMain(int argc, char** argv)
{
    GLMY_TestSection("Utility");
    printf("-> IntRandom: %s\n", GLMY_Test_Random() ? "Failed" : "Success");
    printf("-> StringGenerateRandom: %s\n", GLMY_Test_StringGenerateRandom() ? "Failed" : "Success");

    GLMY_TestSection("HashMap");
    printf("-> HashMap: %s\n", GLMY_Test_HashMap() ? "Failed" : "Success");
    
    return 0;
}

#endif
