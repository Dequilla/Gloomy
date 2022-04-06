#ifndef __GLMY_TEST_HASHMAP_H__
#define __GLMY_TEST_HASHMAP_H__

#include <stdio.h>

#include <gloomy/hashmap.h>
#include <gloomy/time.h>

#include <test/utility.h>

int GLMY_Test_HashMap()
{
    int fails = 0;

    GLMY_TimePrec start,
                  end;

    char* key[] = {"One", "Two", "Three", "Four", "Five", "Six", "Seven"};
    char* value = "Itsa me!";

    //////////////////////////
    // Create 
    GLMY_TestSubSection("Create");
    start = GLMY_TimePrecProcessNow();
    GLMY_HashMap* map = GLMY_HashMapCreate(7, &GLMY_HashMapHashStringDefault, &GLMY_HashMapCmpStringDefault);
    if(!map) 
    {
        printf("Error: Could not create map.\n");
        fails += 1;
    }
    end = GLMY_TimePrecProcessNow();
    printf("Result: %fms\n\n", GLMY_TimePrecToMilliseconds(GLMY_TimePrecDiff(start, end)));
   
    //////////////////////////
    // Insert 
    GLMY_TestSubSection("Insert");
    start = GLMY_TimePrecProcessNow();

    size_t c = 0;
    for(; c < map->capacity; c++)
    {
        GLMY_HashMapBucket* bucket = GLMY_HashMapInsert(map, key[c], value);
        if(!bucket)
        {
            printf("Error: Could not insert (key: %s, value: %s)\n", key[c], value);
            fails += 1;
        }
    }

    end = GLMY_TimePrecProcessNow();
    printf("Result: %fms\n\n", GLMY_TimePrecToMilliseconds(GLMY_TimePrecDiff(start, end)));
    
    //////////////////////////
    // Get 
    GLMY_TestSubSection("Get");
    start = GLMY_TimePrecProcessNow();
    GLMY_Pair pair = GLMY_HashMapGet(map, key[0]);
    if(!pair.key && strcmp(value, pair.value) != 0) 
    {
        printf("Error: Could not get (key: %s)\n", key[0]);
        fails += 1;
    }
    end = GLMY_TimePrecProcessNow();
    printf("Result: %fms\n\n", GLMY_TimePrecToMilliseconds(GLMY_TimePrecDiff(start, end)));

    //////////////////////////
    // Erase

    // TODO
     

    GLMY_HashMapDelete(map);

    return fails;
}

#endif
