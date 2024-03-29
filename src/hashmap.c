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

GLMY_Pair GLMY_HashMapGet(GLMY_HashMap* map, void* key)
{
    GLMY_Pair pair = { NULL, NULL };

    if(!map || !key || map->count <= 0)
        return pair;

    size_t hash = map->calcHash(key);

    size_t index = 0,
           probeIndex = hash % map->capacity;

    while(!map->cmpKey(map->buckets[probeIndex].key, key))
    {
        if((index += 1) >= map->capacity)
            return pair;

        probeIndex = GLMY_HashMapCalcProbeIndex(hash, index,  map->capacity);
    }

    pair.key = map->buckets[probeIndex].key;
    pair.value = map->buckets[probeIndex].value;

    return pair;
}

GLMY_Pair GLMY_HashMapErase(GLMY_HashMap* map, void* key)
{
    GLMY_Pair pair = { NULL, NULL };

    if(!map || !key || map->count <= 0)
        return pair;

    size_t hash = map->calcHash(key);

    size_t index = 0,
           probeIndex = GLMY_HashMapCalcProbeIndex(hash, index,  map->capacity);

    while(!map->cmpKey(map->buckets[probeIndex].key, key))
    {
        if((index += 1) >= map->capacity)
            return pair;

        probeIndex = GLMY_HashMapCalcProbeIndex(hash, index,  map->capacity);
    }
    
    GLMY_HashMapBucket* bucket = &map->buckets[probeIndex];
    pair.key = bucket->key;
    pair.value = bucket->value;

    bucket->value = NULL;
    bucket->key = NULL;
    bucket->hash = 0;

    map->count -= 1; 

    return pair;
}

GLMY_HashMapBucket* GLMY_HashMapAt(GLMY_HashMap* map, size_t index)
{
    if(!map) 
        return NULL;

    if(index >= map->capacity)
        return NULL;

    return &map->buckets[index];
}

bool GLMY_HashMapResize(GLMY_HashMap* map, size_t newSize)
{
    GLMY_HashMapBucket* newBuckets = (GLMY_HashMapBucket*)calloc(sizeof(GLMY_HashMapBucket), newSize);
    if(newBuckets == NULL)
        return false;

    size_t index = 0;
    for(; index < map->capacity; index++)
    {
        GLMY_HashMapBucket* bucket = GLMY_HashMapAt(map, index);
        if(bucket->key == NULL)
            continue;

        size_t  pindex = 0,
                probeIndex = GLMY_HashMapCalcProbeIndex(bucket->hash, pindex, newSize);

        while(map->cmpKey(newBuckets[probeIndex].key, bucket->key))
        {
            if((pindex += 1) >= newSize)
                return false;

            probeIndex = GLMY_HashMapCalcProbeIndex(bucket->hash, pindex,  map->capacity);
        }

        memcpy(&newBuckets[probeIndex], bucket, sizeof(GLMY_HashMapBucket));
    }

    free(map->buckets);
    map->buckets = newBuckets;
    map->capacity = newSize;

    return true;
}


