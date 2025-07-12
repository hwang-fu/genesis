#include <stdlib.h>

#include "vector.h"

owned Vector * vec_new() {
}

copy u64  vec_size(borrowed Vector * vec) {
}

copy u64  vec_capacity(borrowed Vector * vec) {
}

copy Bool vec_is_empty(borrowed Vector * vec) {
}

borrowed void * vec_front(borrowed Vector * vec) {
}

borrowed void * vec_back(borrowed Vector * vec) {
}


owned void * vec_popfront(borrowed Vector * vec) {
}

owned void * vec_popback(borrowed Vector * vec) {
}

owned void * vec_at(borrowed Vector * vec, copy u64 idx) {
}

void vec_pushfront(borrowed Vector * vec, owned void * elem) {
}

void vec_pushback(borrowed Vector * vec, owned void * elem) {
}

void vec_dtor(borrowed Vector * vec, void (*customized_free)(void*)) {
}

void vec_destroy(borrowed Vector * vec, void (*customized_free)(void*)) {
}

void vec_merge(borrowed Vector * vec, owned Vector * vec2) {
}

