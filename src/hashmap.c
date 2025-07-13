#include <stdlib.h>

#include "hashmap.h"
#include "generics.h"
#include "utility.h"
#include "assertf.h"

#define HASHMAP_DEFAULT_CAPACITY (16)
#define HASHMAP_HIGH_WATERMARK   (0.7)
#define HASHMAP_LOW_WATERMARK    (0.4)

static copy u64 fnv1a_hash(borrowed const char * key) {
    unsigned long hash = 14695981039346656037UL;    // FNV offset basis
    for (; *key; ) {
        hash ^= (unsigned char)(*key++);
        hash *= 1099511628211UL;                    // FNV prime
    }
    return hash;
}

static double watermark_(double size, double capacity) {
    return size / capacity;
}

static owned MapEntry * entry_new_(borrowed const char * key, owned void * value) {
    scp(key);
    owned MapEntry * entry = new(sizeof(MapEntry));
    entry->key             = s_copy(key);
    entry->value           = value;
    entry->next            = nil;
    return entry;
}

static void entry_destroy_(owned MapEntry * entry, void (*customized_free)(void*)) {
    if (!entry) {
        return;
    }
    if (!customized_free) {
        customized_free = free;
    }
    sfree(entry->key);
    customized_free(entry->value);
    free(entry);
}

static void entries_destroy_(owned MapEntry * entries, void (*customized_free)(void*)) {
    if (!entries) {
        return;
    }
    if (!customized_free) {
        customized_free = free;
    }
    entries_destroy_(entries->next, customized_free);
    entry_destroy_(entries, customized_free);
}

Map * map_new() {
    owned Map * map = new(sizeof(Map));
    map->slots      = zeros(HASHMAP_DEFAULT_CAPACITY * sizeof(MapEntry*));
    map->size       = 0;
    map->capacity   = HASHMAP_DEFAULT_CAPACITY;
    return map;
}

copy Bool map_insert_key(borrowed Map * map, borrowed const char * key, owned void * value) {
    scp(map);
    scp(key);

    if (map_contains_key(map, key)) {
        return False;
    }

    copy u64 size = map->size;
    copy u64 cap  = map->capacity;
    if (eq(0, cap)) {
        cap = HASHMAP_DEFAULT_CAPACITY;
        map_extend_capacity(map, cap);
    }
    if (watermark_(size, cap) >= HASHMAP_HIGH_WATERMARK) {
        do {
            cap += HASHMAP_DEFAULT_CAPACITY;
        } while (watermark_(size, cap) >= HASHMAP_LOW_WATERMARK);
        map_extend_capacity(map, cap);
    }

    copy  u64        idx   = fnv1a_hash(key) % cap;
    owned MapEntry * entry = map->slots[idx];
    if (entry) {
        while (entry->next) {
            entry = entry->next;
        }
        entry->next = entry_new_(key, value);
    }
    else {
        map->slots[idx] = entry_new_(key, value);
    }

    map->size = size + 1;
    return True;
}

copy Bool map_insert_key_owned(borrowed Map * map, owned char * key, owned void * value) {
    scp(map);
    scp(key);

    if (map_contains_key(map, key)) {
        free(key);
        return False;
    }

    map_insert_key(map, key, value);
    free(key);
    return True;
}

borrowed void * map_get_key(borrowed Map * map, borrowed const char * key) {
    scp(map);
    scp(key);

    if (!map_contains_key(map, key)) {
        return nil;
    }

    copy     u64        idx   = fnv1a_hash(key) % map->capacity;
    borrowed MapEntry * entry = map->slots[idx];
    while (entry) {
        if (s_compare(key, entry->key, 0)) {
            return entry->value;
        }
        entry = entry->next;
    }
    return nil;
}

borrowed void * map_get_key_owned(borrowed Map * map, owned char * key) {
    scp(map);
    scp(key);
    borrowed void * elem = map_get_key(map, key);
    free(key);
    return elem;
}

copy Bool map_is_empty(borrowed Map * map) {
    scp(map);
    return eq(0, map->size);
}

copy Bool map_contains_key(borrowed Map * map, borrowed const char * key) {
    scp(map);
    scp(key);

    if (map_is_empty(map)) {
        return False;
    }

    copy     u64        idx   = fnv1a_hash(key) % map->capacity;
    borrowed MapEntry * entry = map->slots[idx];
    while (entry) {
        if (s_compare(key, entry->key, 0)) {
            return True;
        }
        entry = entry->next;
    }
    return False;
}

copy Bool map_contains_key_owned(borrowed Map * map, owned char * key) {
    scp(map);
    scp(key);
    copy Bool contains = map_contains_key(map, key);
    free(key);
    return contains;
}

copy Bool map_delete_key(borrowed Map * map, borrowed const char * key, borrowed void (*customized_free)(void*)) {
    scp(map);
    scp(key);
    if (!customized_free) {
        customized_free = free;
    }

    copy u64 size = map->size;
    copy u64 cap  = map->capacity;
    copy u64 idx  = fnv1a_hash(key) % cap;
    borrowed MapEntry * entry = map->slots[idx];
    if (!entry) {
        return False;
    }
    if (s_compare(key, entry->key, 0)) {
        map->slots[idx] = entry->next;
        map->size       = size - 1;
        entry_destroy_(entry, customized_free);
        return True;
    }

    borrowed MapEntry * prev = entry;
    entry = entry->next;
    while (entry) {
        if (s_compare(key, entry->key, 0)) {
            prev->next      = entry->next;
            map->slots[idx] = prev;
            map->size       = size - 1;
            entry_destroy_(entry, customized_free);
            return True;
        }
        prev  = entry;
        entry = entry->next;
    }
    return False;
}

copy Bool map_delete_key_owned(borrowed Map * map, owned char * key, borrowed void (*customized_free)(void*)) {
    scp(map);
    scp(key);
    copy Bool deleted = map_delete_key(map, key, customized_free);
    free(key);
    return deleted;
}

void map_extend_capacity(borrowed Map * map, copy u64 newcap) {
    scp(map);
    copy u64 cap = map->capacity;
    if (cap >= newcap) {
        abort(
            "Failed to extend the capacity of the hashmap, "
            "as the original capacity [%lu] is larger than or equal to the new capacity [%lu].",
            cap, newcap);
    }

    owned MapEntry ** entries = zeros(newcap * sizeof(MapEntry*));
    for (copy u64 i = 0; i < cap; i++) {
        borrowed MapEntry * entry = map->slots[i];
        while (entry) {
            borrowed MapEntry * next = entry->next;
            entry->next = nil;
            copy u64 idx = fnv1a_hash(entry->key) % newcap;
            if (entries[idx]) {
                borrowed MapEntry * temp = entries[idx];
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = entry;
            }
            else {
                entries[idx] = entry;
            }
            entry = next;
        }
    }

    free(map->slots);
    map->slots    = entries;
    map->capacity = newcap;
}

void map_dtor(borrowed Map * map, borrowed void (*customized_free)(void*)) {
    if (!map) {
        return;
    }
    if (!customized_free) {
        customized_free = free;
    }

    copy u64 cap = map->capacity;
    for (copy u64 i = 0; i < cap; i++) {
        entries_destroy_(map->slots[i], customized_free);
    }
    sfree(map->slots);
    map->size     = 0;
    map->capacity = 0;
}

void map_destroy(owned Map * map, borrowed void (*customized_free)(void*)) {
    if (!map) {
        return;
    }
    map_dtor(map, customized_free);
    free(map);
}

