#include "utility.h"
#include "generics.h"

copy Bool is_c_digit(copy const char c) {
    return ('0' <= c) && (c <= '9');
}

copy Bool is_c_bdigit(copy const char c) {
    return eq('0', c) || eq('1', c);
}

copy Bool is_c_odigit(copy const char c) {
    return ('0' <= c) && (c <= '7');
}

copy Bool is_c_xdigit(copy const char c) {
    return (('0' <= c) && (c <= '9'))
        || (('a' <= c) && (c <= 'f'))
        || (('A' <= c) && (c <= 'F'))
    ;
}

