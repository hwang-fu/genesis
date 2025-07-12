#include <stdlib.h>

#include "vector.h"
#include "assertf.h"
#include "generics.h"

#define VECTOR_DEFAULT_CAPACITY (20)
#define HIGH_WATERMARK          (.7)
#define LOW_WATERMARK           (.5)

static copy f64 watermark_(copy f64 size, copy f64 cap) {
    return size / cap;
}

static void extend_capacity_(borrowed Vector * vec, copy u64 newcap) {
    if (vec->size > newcap) {
        error(
            "Failed to extend the vector capacity, "
            "because the size of the vector [%lu] is bigger than the new capacity [%lu].",
            vec->size, newcap);
    }
    vec->data     = realloc(vec->data, newcap * sizeof(void*));
    vec->capacity = newcap;
    scp(vec->data);
}

owned Vector * vec_new() {
    owned Vector * vec = new(sizeof(Vector));
    vec->size          = 0;
    vec->capacity      = VECTOR_DEFAULT_CAPACITY;
    vec->data          = new(VECTOR_DEFAULT_CAPACITY * sizeof(void*));
    return vec;
}

copy u64 vec_size(borrowed Vector * vec) {
    scp(vec);
    return vec->size;
}

copy u64 vec_capacity(borrowed Vector * vec) {
    scp(vec);
    return vec->capacity;
}

copy f64 vec_watermark(borrowed Vector * vec) {
    scp(vec);
    return watermark_(vec->size, vec->capacity);
}

copy Bool vec_is_empty(borrowed Vector * vec) {
    scp(vec);
    if (eq(0, vec->size)) {
        return True;
    }
    else {
        return False;
    }
}

copy Bool vec_resize(borrowed Vector * vec, copy u64 newcap) {
    scp(vec);
    if (vec->size >= newcap) {
        return False;
    }
    extend_capacity_(vec, newcap);
    return True;
}

borrowed void * vec_front(borrowed Vector * vec) {
    scp(vec);
    if (eq(0, vec->size)) {
        return nil;
    }
    return vec->data[0];
}

borrowed void * vec_back(borrowed Vector * vec) {
    scp(vec);
    if (eq(0, vec->size)) {
        return nil;
    }
    return vec->data[vec->size - 1];
}

owned void * vec_popfront(borrowed Vector * vec) {
    scp(vec);
    copy u64 size = vec->size;
    if (eq(0, size)) {
        return nil;
    }
    owned void * data = vec->data[0];
    for (copy u64 i = 0; i < size; i++) {
        vec->data[i] = vec->data[i + 1];
    }
    vec->size = size - 1;
    return data;
}

owned void * vec_popback(borrowed Vector * vec) {
    scp(vec);
    copy u64 size = vec->size;
    if (eq(0, size)) {
        return nil;
    }
    vec->size = size - 1;
    return vec->data[size - 1];
}

owned void * vec_at(borrowed Vector * vec, copy u64 idx) {
    scp(vec);
    if (vec->size <= idx) {
        return nil;
    }
    return vec->data[idx];;
}

void vec_pushfront(borrowed Vector * vec, owned void * elem) {
    scp(vec);
    scp(elem);

    copy u64 size = vec->size;
    copy u64 cap  = vec->capacity;
    if (eq(0, cap)) {
        cap = VECTOR_DEFAULT_CAPACITY;
        extend_capacity_(vec, cap);
    }
    if (watermark_(size, cap) >= HIGH_WATERMARK) {
        do {
            cap *= 2;
        } while (watermark_(size, cap) > LOW_WATERMARK);
        extend_capacity_(vec, cap);
    }

    for (copy u64 i = size; i > 0; i--) {
        vec->data[i] = vec->data[i-1];
    }

    vec->data[0] = elem;
    vec->size    = size + 1;
}

void vec_pushback(borrowed Vector * vec, owned void * elem) {
    scp(vec);
    scp(elem);

    copy u64 size = vec->size;
    copy u64 cap  = vec->capacity;
    if (eq(0, cap)) {
        cap = VECTOR_DEFAULT_CAPACITY;
        extend_capacity_(vec, cap);
    }
    if (watermark_(size, cap) >= HIGH_WATERMARK) {
        do {
            cap *= 2;
        } while (watermark_(size, cap) > LOW_WATERMARK);
        extend_capacity_(vec, cap);
    }

    vec->data[size] = elem;
    vec->size       = size + 1;
}

void vec_dtor(borrowed Vector * vec, void (*customized_free)(void*)) {
    scp(vec);
    if (!customized_free) {
        customized_free = free;
    }

    copy u64 size = vec->size;
    for (u64 i = 0; i < size; i++) {
        customized_free(vec->data[i]);
    }

    vec->size = 0;
    vec->capacity = 0;
    sfree(vec->data);
}

void vec_destroy(borrowed Vector * vec, void (*customized_free)(void*)) {
    scp(vec);
    if (!customized_free) {
        customized_free = free;
    }
    vec_dtor(vec, customized_free);
    free(vec);
}

void vec_merge(borrowed Vector * vec, owned Vector * vec2) {
    scp(vec);
}

