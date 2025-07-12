#include <stdio.h>
#include <stdlib.h>

#include "generics.h"

void * new_(u64 bytes) {
    void * ptr = malloc( bytes );
    if ( !ptr ) {
        fprintf(
            stderr, "Error: Failed to allocate %lu bytes in the heap!\n", 
            bytes
        );
        exit( EXIT_FAILURE );
    }
    return ptr;
}

void * zeros_(u64 bytes) {
    void * ptr = calloc(bytes, sizeof(char));
    if ( !ptr ) {
        fprintf(
            stderr, "Error: Failed to allocate %lu bytes in the heap!\n", 
            bytes
        );
        exit( EXIT_FAILURE );
    }
    return ptr;
}

