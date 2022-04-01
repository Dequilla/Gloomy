#ifndef __GLMY_HASHMAP_H__
#define __GLMY_HASHMAP_H__

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Tips implement hashtable
// 1. Use prime for size
// 2. Quadratic probing for finding open spot if hash is not available
//      2.1 Basically index = Mod(Hash(x) + i^2)
// 3. Double to the nearest prime number when full
// LINK: https://stackoverflow.com/questions/22437416/best-way-to-resize-a-hash-table

// Function pointer of hash function
typedef size_t (*HashCalc)(void*);
size_t GLMY_HashMapHashStringDefault(void* data);

// Function to compare data
typedef bool (*HashCmp)(void*, void*);
bool GLMY_HashMapCmpStringDefault(void* keyLeft, void* keyRight);

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
    HashCmp cmpHash;
} GLMY_HashMap;

GLMY_HashMap* GLMY_HashMapCreate(size_t capacity, HashCalc hashFunc, HashCmp cmpHash);

void GLMY_HashMapDelete(GLMY_HashMap* map);

void* GLMY_HashMapInsert(GLMY_HashMap* map, void* key, void* value);


#endif
