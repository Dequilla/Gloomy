#include <gloomy/hashmap.h>

GLMY_HashMap* GLMY_HashMapCreate(size_t capacity, HashFunc hashFunc)
{
    GLMY_HashMap* map = (GLMY_HashMap*)calloc(sizeof(GLMY_HashMap), 1);
    if(map == NULL) return NULL;

    map->buckets = (GLMY_HashMapBucket*)calloc(sizeof(GLMY_HashMapBucket), capacity);
    if(map->buckets == NULL)
    {
        free(map);
        return NULL;
    }

    map->calcHash = hashFunc;
    map->capacity = capacity;
    map->count = 0;

    return map;
}