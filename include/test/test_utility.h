#ifndef __GLMY_TEST_TESTING_UTILITY_H__
#define __GLMY_TEST_TESTING_UTILITY_H__

#include <test/utility.h>

#define COUNT 10000
#define LOWER_BOUND -928375
#define HIGHER_BOUND 825794

int GLMY_Test_Random()
{
    size_t index = 0;
    int randInt = 0;
    int fails = 0;
    for(; index < COUNT; index++)
    {
        randInt = GLMY_IntRandom(LOWER_BOUND, HIGHER_BOUND);
        if(randInt > HIGHER_BOUND || randInt < LOWER_BOUND)
        {
            fails += 1;
            printf("ERROR: GLMY_IntRandom failed on (generated: %d, min: %d, max: %d)\n", randInt, LOWER_BOUND, HIGHER_BOUND);
        }
    }

    return fails;
}

int GLMY_Test_StringGenerateRandom()
{
    int fails = 0;

    size_t count = 0;
    for(; count < 100; count++)
    {
        int size = GLMY_IntRandom(10, 100);
        char* randStr = GLMY_StringGenerateRandom(size); 
        if(randStr == NULL)
        {
            fails += 1;
            printf("ERROR: Failed, out of memory.");
            return fails;
        }

        if(strlen(randStr) != (size - 1))
        {
            fails += 1;
            printf("ERROR: Failed, generated string is not equal to requested size (requested: %d, actual: %ld)", size, strlen(randStr));
        }

        free(randStr);
    }

    return fails;
    
}

#endif
