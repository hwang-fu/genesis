#include <stdlib.h>

#include "label.h"
#include "assertf.h"
#include "generics.h"
#include "utility.h"

owned static char * LPrefix = nil;
copy  static u64    LCount  = 0;

void label_ctor() {
    assert_eq(nil, LPrefix);
    LPrefix = s_copy("L.");
}

void label_dtor() {
    sfree(LPrefix);
    LCount = 0;
}

owned char * label_new() {
    owned char * suffix = s_from_u64(LCount);
    if (eq(0xffffffffffffffff, LCount)) {
        LCount = 0;
        LPrefix = s_insert_c_end_owned(LPrefix, '.');
    }
    else {
        LCount += 1;
    }
    owned char * label = s_insert_end(LPrefix, suffix);
    free(suffix);
    return label;
}

owned char * s_unique() {
    return label_new();
}

