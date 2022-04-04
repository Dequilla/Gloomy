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


size_t GLMY_HashMapCalcProbeIndex(size_t hash, size_t index, size_t capacity)
{
    return  (hash + index) % capacity;
}

GLMY_HashMap* GLMY_HashMapCreate(size_t capacity, HashCalc hashFunc, KeyCmp cmpKey)
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
    map->cmpKey = cmpKey;
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
        map->cmpKey = NULL;
        free(map);
    }
}

GLMY_HashMapBucket* GLMY_HashMapInsert(GLMY_HashMap* map, void* key, void* value)
{
    if(!key || !value || !map) 
        return NULL;

    // TODO: Resize
    if(map->capacity <= map->count)
        return NULL;

    size_t hash = map->calcHash(key);

    size_t index = 0,
           probeIndex = GLMY_HashMapCalcProbeIndex(hash, index,  map->capacity);

    if(map->cmpKey(map->buckets[probeIndex].key, key))
        return NULL;

    while(map->buckets[probeIndex].key != NULL)
    {
        if((index += 1) >= map->capacity)
            return NULL;

        probeIndex = GLMY_HashMapCalcProbeIndex(hash, index,  map->capacity);

        if(map->cmpKey(map->buckets[probeIndex].key, key))
            return NULL;
    }

    GLMY_HashMapBucket* bucket = &(map->buckets[probeIndex]);
    bucket->hash = hash;
    bucket->key = key;
    bucket->value = value;

    map->count += 1;

    return bucket;
}

void* GLMY_HashMapGet(GLMY_HashMap* map, void* key)
{
    if(!map || !key || map->count <= 0)
        return NULL;

    size_t hash = map->calcHash(key);

    size_t index = 0,
           probeIndex = hash % map->capacity;

    while(!map->cmpKey(map->buckets[probeIndex].key, key))
    {
        if((index += 1) >= map->capacity)
            return NULL;

        probeIndex = GLMY_HashMapCalcProbeIndex(hash, index,  map->capacity);
    }

    return map->buckets[probeIndex].value;
}

GLMY_HashMapBucket* GLMY_HashMapAt(GLMY_HashMap* map, size_t index)
{
    if(!map) 
        return NULL;

    if(index >= map->capacity)
        return NULL;

    return &map->buckets[index];
}

bool GLMY_HashMapErase(GLMY_HashMap* map, void* key)
{
    if(!map || !key || map->count <= 0)
        return NULL;

    size_t hash = map->calcHash(key);

    size_t index = 0,
           probeIndex = hash % map->capacity;

    while(!map->cmpKey(map->buckets[probeIndex].key, key))
    {
        if((index += 1) >= map->capacity)
            return NULL;

        probeIndex = (hash + index) % map->capacity;
    }
 
}

