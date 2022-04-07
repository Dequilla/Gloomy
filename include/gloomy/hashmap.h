#ifndef __GLMY_HASHMAP_H__
#define __GLMY_HASHMAP_H__

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <gloomy/utility.h>

// Function pointer of hash function
typedef size_t (*HashCalc)(void*);
size_t GLMY_HashMapHashStringDefault(void* data);

// Function to compare key
typedef bool (*KeyCmp)(void*, void*);
bool GLMY_HashMapCmpStringDefault(void* keyLeft, void* keyRight);

size_t GLMY_HashMapCalcProbeIndex(size_t hash, size_t index, size_t capacity);

typedef struct {
    size_t hash;

    void* key;
    void* value;
} GLMY_HashMapBucket;

typedef struct {
    GLMY_HashMapBucket* buckets;
    size_t capacity;
    size_t count;

    HashCalc calcHash;     
    KeyCmp cmpKey;
} GLMY_HashMap;

GLMY_HashMap* GLMY_HashMapCreate(size_t capacity, HashCalc hashFunc, KeyCmp cmpKey);

void GLMY_HashMapDelete(GLMY_HashMap* map);

GLMY_HashMapBucket* GLMY_HashMapInsert(GLMY_HashMap* map, void* key, void* value);

GLMY_Pair GLMY_HashMapGet(GLMY_HashMap* map, void* key);

GLMY_Pair GLMY_HashMapErase(GLMY_HashMap* map, void* key);

GLMY_HashMapBucket* GLMY_HashMapAt(GLMY_HashMap* map, size_t index);

bool GLMY_HashMapResize(GLMY_HashMap* map, size_t newSize);

#endif
