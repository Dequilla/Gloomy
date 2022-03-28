#ifndef __GLMY_TEST_HASHMAP_H__
#define __GLMY_TEST_HASHMAP_H__

#include <stdio.h>

#include <gloomy/hashmap.h>
#include <gloomy/time.h>

int GLMY_Test_HashMap()
{
    puts(" --- Test HashMap Start --- ");
   


    GLMY_TimePrec start = GLMY_TimePrecProcessNow();
    GLMY_HashMap* map = GLMY_HashMapCreate(100, &GLMY_HashMapHashStringDefault);
    GLMY_TimePrec end = GLMY_TimePrecProcessNow();

    printf("Creating HashMap took: %fms\n", GLMY_TimePrecToMilliseconds(GLMY_TimePrecDiff(start, end))); 



    puts(" ---  Test HashMap End  --- ");
    return 1;
}

#endif
