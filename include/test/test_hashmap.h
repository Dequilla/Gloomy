#ifndef __GLMY_TEST_HASHMAP_H__
#define __GLMY_TEST_HASHMAP_H__

#include <stdio.h>

#include <gloomy/hashmap.h>

int GLMY_Test_HashMap()
{
    puts("--- Test HashMap ---");

    GLMY_HashMap* map = GLMY_HashMapCreate(100, &GLMY_HashMapHashStringDefault);

    return 0;
}

#endif
