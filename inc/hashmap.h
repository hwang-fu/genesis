#ifndef GENESIS_HASHMAP_H
#define GENESIS_HASHMAP_H

#include "generics.h"

typedef struct MapEntry MapEntry;
struct MapEntry {
    owned char         * key;
    owned void         * value;
    owned MapEntry     * next;
};

typedef struct Map Map;
struct Map {
    owned MapEntry ** slots;
    copy  u64         size;
    copy  u64         capacity;
};

Map * map_new();

copy Bool map_insert_key(borrowed Map * map, borrowed const char * key, owned void * value);
copy Bool map_insert_key_owned(borrowed Map * map, owned char * key, owned void * value);
borrowed void * map_get_key(borrowed Map * map, borrowed const char * key);
borrowed void * map_get_key_owned(borrowed Map * map, owned char * key);

copy Bool map_is_empty(borrowed Map * map);
copy Bool map_contains_key(borrowed Map * map, borrowed const char * key);

copy Bool map_delete_key(borrowed Map * map, borrowed const char * key, borrowed void (*customized_free)(void*));
copy Bool map_delete_key_owned(borrowed Map * map, owned char * key, borrowed void (*customized_free)(void*));

void map_extend_capacity(borrowed Map * map, copy u64 newcap);

void map_dtor(borrowed Map * map, borrowed void (*customized_free)(void*));
void map_destroy(owned Map * map, borrowed void (*customized_free)(void*));

#endif // GENESIS_HASHMAP_H
