#ifndef __GLMY_TEST_HASHMAP_H__
#define __GLMY_TEST_HASHMAP_H__

#include <stdio.h>

#include <gloomy/hashmap.h>
#include <gloomy/time.h>

#include <test/test_utility.h>

int GLMY_Test_HashMap()
{
    GLMY_TestSection("Hash Map");

    GLMY_TestSubSection("Creating 1000x100");
    GLMY_TimePrec start = GLMY_TimePrecProcessNow();

    size_t count = 0;
    for(; count < 1000; count++)
    {
        GLMY_HashMap* map = GLMY_HashMapCreate(100, &GLMY_HashMapHashStringDefault, &GLMY_HashMapCmpStringDefault);
        GLMY_HashMapInsert(map, "Test", "Value!");
        GLMY_HashMapDelete(map);
    }

    GLMY_TimePrec end = GLMY_TimePrecProcessNow();
    printf("Result: %fms\n\n", GLMY_TimePrecToMilliseconds(GLMY_TimePrecDiff(start, end))); 

    GLMY_TestSubSection("Creating 1000x100000");
    start = GLMY_TimePrecProcessNow();

    count = 0;
    for(; count < 1000; count++)
    {
        GLMY_HashMap* map = GLMY_HashMapCreate(100000, &GLMY_HashMapHashStringDefault, &GLMY_HashMapCmpStringDefault);
        GLMY_HashMapDelete(map);
    }

    end = GLMY_TimePrecProcessNow();
    printf("Result: %fms\n\n", GLMY_TimePrecToMilliseconds(GLMY_TimePrecDiff(start, end)));

    return 1;
}

#endif
