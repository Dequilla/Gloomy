#include <gloomy/hashmap.h>

size_t GLMY_HashMapHashStringDefault(void* data)
{
    size_t accumilator = 0,
           index = 0;
    
    char* string = (char*)data;

    for(; string[index] != '\0'; index++)
        accumilator += string[index];

    return accumilator;
}

bool GLMY_HashMapCmpStringDefault(void* keyLeft, void* keyRight)
{
    if(!keyLeft || !keyRight) return false;

    return 0 == strcmp(keyLeft, keyRight);
}

GLMY_HashMap* GLMY_HashMapCreate(size_t capacity, HashCalc hashFunc, HashCmp cmpHash)
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
    map->cmpHash = cmpHash;
    map->capacity = capacity;
    map->count = 0;

    return map;
}

void GLMY_HashMapDelete(GLMY_HashMap* map)
{
    if(map)
    {
        free(map->buckets);
        map->calcHash = NULL;
        map->cmpHash = NULL;
        free(map);
    }
}

void* GLMY_HashMapInsert(GLMY_HashMap* map, void* key, void* value)
{
    if(map->capacity <= map->count)
        return NULL;

    if(!key || !value) 
        return NULL;

    size_t hash = map->calcHash(key);

    size_t index = 0,
           probeIndex = 0;

    while(map->cmpHash(map->buckets[probeIndex].key, key))
    {
        // Quadratic probing for finding open spot if hash is not available
        // Basically index = Mod(Hash(x) + i^2, capacity)
        index += 1;
        probeIndex = map->capacity % (hash + probeIndex * probeIndex);
    }

    GLMY_HashMapBucket bucket = map->buckets[probeIndex];
    bucket.hash = hash;
    bucket.key = key;
    bucket.value = value;

    map->count += 1;
}


