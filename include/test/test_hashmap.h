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
    GLMY_HashMap* map = GLMY_HashMapCreate(7, &GLMY_HashMapHashStringDefault, &GLMY_HashMapCmpStringDefault);
    if(!map) 
    {
        printf("Error: Could not create map.\n");
        fails += 1;
    }
   
    //////////////////////////
    // Insert 
    GLMY_TestSubSection("Insert");
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
    
    //////////////////////////
    // Get 
    GLMY_TestSubSection("Get");
    GLMY_Pair pair = GLMY_HashMapGet(map, key[0]);
    if(!pair.key && strcmp(value, pair.value) != 0) 
    {
        printf("Error: Could not get (key: %s)\n", key[0]);
        fails += 1;
    }

    //////////////////////////
    // Erase
    GLMY_TestSubSection("Erase");
    GLMY_Pair eraseRes = GLMY_HashMapErase(map, key[0]);
    if(!eraseRes.key || strcmp(value, eraseRes.value) != 0)
    {
        printf("Error: Could not erase (key: %s)\n", key[0]);
        fails += 1;
    }


    //////////////////////////
    // Resize
    GLMY_TestSubSection("Resize");
    bool resized = GLMY_HashMapResize(map, 120);
    if(!resized || map->capacity != 120)
    {
        printf("Error: Could not resize map (newSize: %d)\n", 120);
        fails += 1;
    }

    GLMY_HashMapDelete(map);

    return fails;
}

#endif
