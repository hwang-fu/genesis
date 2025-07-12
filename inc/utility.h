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

borrowed const char * s_localtime();

#endif // GENESIS_UTILITY_H
