#ifndef GENESIS_UTILITY_H
#define GENESIS_UTILITY_H

#include "generics.h"

copy Bool is_c_digit(copy const char c);
copy Bool is_c_bdigit(copy const char c);
copy Bool is_c_odigit(copy const char c);
copy Bool is_c_xdigit(copy const char c);

copy Bool is_c_upper(copy const char c);
copy Bool is_c_lower(copy const char c);
copy Bool is_c_letter(copy const char c);

copy Bool is_c_alpha(copy const char c);
copy Bool is_c_alnum(copy const char c);
copy Bool is_c_whitespace(copy const char c);
copy Bool is_c_op(copy const char c);

borrowed const char * s_localtime();

owned char * s_copy(borrowed const char * s);

owned char * s_insert_end(borrowed const char * base, borrowed const char * suffix);
owned char * s_insert_end_owned(owned char * base, borrowed const char * suffix);

owned char * s_insert_front(borrowed const char * base, borrowed const char * prefix);
owned char * s_insert_front_owned(owned char * base, borrowed const char * prefix);

owned char * s_insert_c_end(borrowed const char * base, copy const char c);
owned char * s_insert_c_end_owned(owned char * base, copy const char c);

owned char * s_insert_c_front(borrowed const char * base, copy const char c);
owned char * s_insert_c_front_owned(owned char * base, copy const char c);

copy Bool s_compare(borrowed const char * s1, borrowed const char * s2, copy const u64 n);

copy Bool s_startswith(borrowed const char * s, borrowed const char * prefix);
copy Bool s_endswith(borrowed const char * s, borrowed const char * suffix);

owned char * c_tostr(copy const char c);

copy Bool is_s_integer(borrowed const char * s);
copy Bool is_s_integer_owned(owned char * s);
copy Bool is_s_float(borrowed const char * s);
copy Bool is_s_float_owned(owned char * s);

copy u64 s_to_u64(borrowed const char * s);
copy u64 s_to_u64_owned(owned char * s);

#endif // GENESIS_UTILITY_H
