#include <stdlib.h>

#include "label.h"
#include "assertf.h"
#include "generics.h"
#include "utility.h"

owned static char * LPrefix = nil;
copy  static u64    LCount  = 0;
copy  static u64    Counter = 0;

void label_init() {
    assert_eq(nil, LPrefix);
    LPrefix = s_copy("L.");
}

void label_fin() {
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
    return s_insert_front_owned(suffix, LPrefix);
}

owned char * s_unique() {
    owned char * suffix = s_from_u64(Counter);
    if (eq(0xffffffffffffffff, Counter)) {
        Counter = 0;
    }
    else {
        Counter += 1;
    }
    return s_insert_front_owned(suffix, "___ANONYMOUS");
}

