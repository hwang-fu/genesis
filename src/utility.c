#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "crayon.h"
#include "utility.h"
#include "assertf.h"
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

borrowed const char * s_localtime() {
    borrowed static char buffer[100] = { 0 };

    copy time_t now = time(nil);
    borrowed struct tm * lt = localtime(&now);
    if (!lt) {
        fprintf(
            stderr, 
            RED BOLD "ERROR: " ENDCRAYON "failed to parse the local time."
        );
        exit( EXIT_FAILURE );
    }

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", lt);

    return buffer;
}

owned char * s_copy(borrowed const char * s) {
    if (!s) {
        s = "";
    }
    owned char * copied = strdup(s);
    scp(copied);
    return copied;
}

owned char * s_insert_end(borrowed const char * base, borrowed const char * suffix) {
    if (eq(nil, base) && eq(nil, suffix)) {
        return s_copy("");
    }
    if (eq(nil, suffix)) {
        return s_copy(base);
    }
    if (eq(nil, base)) {
        return s_copy(suffix);
    }
    copy u64 len1 = strlen(base);
    copy u64 len2 = strlen(suffix);
    copy u64 len = len1 + len2 + 1;
    owned char * s = new(len * sizeof(char));
    for (copy u64 i = 0; i < len; i++) {
        s[i] = (i < len1) ? base[i] : suffix[i-len1];
    }
    s[len] = '\0';
    return s;
}

owned char * s_insert_end_owned(owned char * base, borrowed const char * suffix) {
    if (eq(nil, base) && eq(nil, suffix)) {
        return s_copy("");
    }
    if (eq(nil, suffix)) {
        owned char * s = s_copy(base);
        free(base);
        return s;
    }
    if (eq(nil, base)) {
        return s_copy(suffix);
    }
    copy u64 len1 = strlen(base);
    copy u64 len2 = strlen(suffix);
    copy u64 len = len1 + len2 + 1;
    owned char * s = new(len * sizeof(char));
    for (copy u64 i = 0; i < len; i++) {
        s[i] = (i < len1) ? base[i] : suffix[i-len1];
    }
    s[len] = '\0';
    free(base);
    return s;
}

owned char * s_insert_front(borrowed const char * base, borrowed const char * prefix) {
    if (eq(nil, base) && eq(nil, prefix)) {
        return s_copy("");
    }
    if (eq(nil, prefix)) {
        return s_copy(base);
    }
    if (eq(nil, base)) {
        return s_copy(prefix);
    }
    copy u64 len1 = strlen( prefix );
    copy u64 len2 = strlen( base );
    copy u64 len = len1 + len2 + 1;
    owned char * s = new(len * sizeof(char));
    for (copy u64 i = 0; i < len; i++) {
        s[i] = (i < len1) ? prefix[i] : base[i-len1];
    }
    s[len] = '\0';
    return s;
}

owned char * s_insert_front_owned(owned char * base, borrowed const char * prefix) {
    if (eq(nil, base) && eq(nil, prefix)) {
        return s_copy("");
    }
    if (eq(nil, prefix)) {
        owned char * s = s_copy(base);
        free(base);
        return s;
    }
    if (eq(nil, base)) {
        return s_copy(prefix);
    }
    copy u64 len1 = strlen( prefix );
    copy u64 len2 = strlen( base );
    copy u64 len = len1 + len2 + 1;
    owned char * s = new(len * sizeof(char));
    for (copy u64 i = 0; i < len; i++) {
        s[i] = (i < len1) ? prefix[i] : base[i-len1];
    }
    s[len] = '\0';
    free(base);
    return s;
}

owned char * s_insert_c_end(borrowed const char * base, copy const char c) {
    if (eq(nil, base)) {
        return c_tostr(c);
    }
    u64 len1 = strlen( base );
    u64 len2 = 1;
    u64 len = len1 + len2 + 1;
    char * s = new(len * sizeof(char));
    for (u64 i = 0; i < len1; i++) {
        s[i] = base[i];
    }
    s[len1] = c;
    s[len] = '\0';
    return s;
}

owned char * s_insert_c_end_owned(owned char * base, copy const char c) {
    if (eq(nil, base)) {
        return c_tostr(c);
    }
    u64 len1 = strlen( base );
    u64 len2 = 1;
    u64 len = len1 + len2 + 1;
    char * s = new(len * sizeof(char));
    for (u64 i = 0; i < len1; i++) {
        s[i] = base[i];
    }
    s[len1] = c;
    s[len] = '\0';
    free(base);
    return s;
}

owned char * s_insert_c_front(borrowed const char * base, copy const char c) {
    if (eq(nil, base)) {
        return c_tostr(c);
    }
    u64 len1 = 1;
    u64 len2 = strlen( base );
    u64 len = len1 + len2 + 1;
    char * s = new(len * sizeof(char));
    s[0] = c;
    for (u64 i = 0; i < len2; i++) {
        s[i+1] = base[i];
    }
    s[len] = '\0';
    return s;
}

owned char * s_insert_c_front_owned(owned char * base, copy const char c) {
    if (eq(nil, base)) {
        return c_tostr(c);
    }
    u64 len1 = 1;
    u64 len2 = strlen( base );
    u64 len = len1 + len2 + 1;
    char * s = new(len * sizeof(char));
    s[0] = c;
    for (u64 i = 0; i < len2; i++) {
        s[i+1] = base[i];
    }
    s[len] = '\0';
    free(base);
    return s;
}

copy Bool s_compare(borrowed const char * s1, borrowed const char * s2, copy const u64 n) {
    if (eq(nil, s1) && eq(nil, s2)) {
        return True;
    }
    if (eq(nil, s1)) {
        return False;
    }
    if (eq(nil, s2)) {
        return False;
    }

    if (n == 0) {   // compare the whole s1 and s2.
        return eq(0, strcmp(s1, s2));
    } 
    for (copy u64 i = 0; i < n; i++) {
        if (eq(s1[i], '\0') && eq(s2[i], '\0')) {
            return True;
        }
        if (neq(s1[i], s2[i])) {
            return False;
        }
        if (eq(s1[i], '\0')) {
            return False;
        }
        if (eq(s2[i], '\0')) {
            return False;
        }
    }
    return True;
}

copy Bool s_startswith(borrowed const char * s, borrowed const char * prefix) {
    if (eq(nil, s) && eq(nil, prefix)) {
        return True;
    }
    if (eq(nil, s)) {
        return False;
    }
    if (eq(nil, prefix)) {
        return False;
    }
    if (strlen(s) < strlen(prefix)) {
        return False;
    }
    if (strlen(s) > 0 && strlen(prefix) == 0) {
        return False;
    }

    copy u64 len = strlen(prefix);
    for (copy u64 i = 0; i < len; i++) {
        if (neq(s[i], prefix[i])) {
            return False;
        }
    }
    return True;
}

copy Bool s_endswith(borrowed const char * s, borrowed const char * suffix) {
    if (eq(nil, s) && eq(nil, suffix)) {
        return True;
    }
    if (eq(nil, s)) {
        return False;
    }
    if (eq(nil, suffix)) {
        return False;
    }
    if (strlen(s) < strlen(suffix)) {
        return False;
    }
    if (strlen(s) > 0 && strlen(suffix) == 0) {
        return False;
    }

    copy u64 size = strlen(s);
    copy u64 len  = strlen(suffix);
    for (copy u64 i = 0; i < len; i++) {
        if (neq(s[size-i-1], suffix[len-i-i])) {
            return False;
        }
    }
    return True;
}

owned char * c_tostr(copy const char c) {
    owned char * p = new( 2 );
    p[0] = c;
    p[1] = '\0';
    return p;
}

static Bool is_s_xinteger(borrowed const char * s) {
    if (!s_startswith(s, "0x") && !s_startswith(s, "0X")) {
        return False;
    }
    pforward(s, 2);
    do {
        if (!is_c_xdigit(deref(s, char))) {
            return False;
        }
        pforward(s, 1);
    } while (deref(s, char));
    return True;
}

static Bool is_s_ointeger(borrowed const char * s) {
    if (!s_startswith(s, "0o") && !s_startswith(s, "0O")) {
        return False;
    }
    pforward(s, 2);
    do {
        if (!is_c_odigit(deref(s, char))) {
            return False;
        }
        pforward(s, 1);
    } while (deref(s, char));
    return True;
}

static Bool is_s_binteger(borrowed const char * s) {
    if (!s_startswith(s, "0b") && !s_startswith(s, "0B")) {
        return False;
    }
    pforward(s, 2);
    do {
        if (!is_c_bdigit(deref(s, char))) {
            return False;
        }
        pforward(s, 1);
    } while (deref(s, char));
    return True;
}

static Bool is_s_dinteger(borrowed const char * s) {
    do {
        if (!is_c_digit(deref(s, char))) {
            return False;
        }
        pforward(s, 1);
    } while (deref(s, char));
    return True;
}

copy Bool is_s_integer(borrowed const char * s) {
    if (!s) {
        return False;
    }
    if (eq(0, strlen(s))) {
        return False;
    }

    if (s_startswith(s, "0x") || s_startswith(s, "0X")) {
        return is_s_xinteger(s);
    }
    else if (s_startswith(s, "0o") || s_startswith(s, "0O")) {
        return is_s_ointeger(s);
    }
    else if (s_startswith(s, "0b") || s_startswith(s, "0B")) {
        return is_s_binteger(s);
    }
    else {
        return is_s_dinteger(s);
    }
}

copy Bool is_s_integer_owned(owned char * s) {
    if (!s) {
        return False;
    }
    if (eq(0, strlen(s))) {
        drop(s);
        return False;
    }

    copy Bool result = is_s_integer_owned(s);
    drop(s);
    return result;
}

copy Bool is_s_float(borrowed const char * s) {
    TODO("%s is to be implemented", __FUNCTION__);
}

copy Bool is_s_float_owned(owned char * s) {
    if (!s) {
        return False;
    }
    if (eq(0, strlen(s))) {
        drop(s);
        return False;
    }

    copy Bool result = is_s_float(s);
    drop(s);
    return result;
}

copy u64 s_to_u64(borrowed const char * s) {
    TODO("%s is to be implemented", __FUNCTION__);
    if (!is_s_integer(s)) {
        abort("Expecting [%s] is a valid integer string.", s);
    }
}

copy u64 s_to_u64_owned(owned char * s) {
    copy u64 result = s_to_u64(s);
    drop(s);
    return result;
}

