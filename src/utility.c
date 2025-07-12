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

copy Bool is_c_upper(copy const char c) {
    return ('A' <= c) && (c <= 'Z');
}

copy Bool is_c_lower(copy const char c) {
    return ('a' <= c) && (c <= 'z');
}

copy Bool is_c_letter(copy const char c) {
    return is_c_upper(c) || is_c_lower(c);
}

copy Bool is_c_alpha(copy const char c) {
    return is_c_letter(c) || eq('_', c);
}

copy Bool is_c_alnum(copy const char c) {
    return is_c_alpha(c) || is_c_digit(c);
}

copy Bool is_c_whitespace(copy const char c) {
    return eq(' ' , c)
        || eq('\t', c)
        || eq('\r', c)
        || eq('\n', c)
    ;
}



