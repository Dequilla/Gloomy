#ifndef __GLMY_TEST_MAIN_H__
#define __GLMY_TEST_MAIN_H__

#include <stdio.h>

#include <test/test_hashmap.h>

int GLMY_TestMain(int argc, char** argv)
{
    int result = GLMY_Test_HashMap();
    printf(" -> HashMap: %s\n", result ? "Success" : "Failed");
    
    return 0;
}

#endif
