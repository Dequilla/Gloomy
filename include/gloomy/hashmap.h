#ifndef __GLMY_HASHMAP_H__
#define __GLMY_HASHMAP_H__

#include <stdlib.h>

// Tips implement hashtable
// 1. Use prime for size
// 2. Quadratic probing for finding open spot if hash is not available
//      2.1 Basically index = Mod(Hash(x) + i^2)
// 3. Double to the nearest prime number when full
// LINK: https://stackoverflow.com/questions/22437416/best-way-to-resize-a-hash-table

// Function pointer of hash function
typedef size_t (*HashFunc)(void*);
size_t GLMY_HashMapHashStringDefault(void* data);

typedef struct {
    size_t hash;

    void* key;
    void* value;
} GLMY_HashMapBucket;

typedef struct {
    GLMY_HashMapBucket* buckets;
    size_t capacity;
    size_t count;

    HashFunc calcHash;     
} GLMY_HashMap;

GLMY_HashMap* GLMY_HashMapCreate(size_t capacity, HashFunc hashFunc);

void GLMY_HashMapDelete(GLMY_HashMap* map);


#endif
