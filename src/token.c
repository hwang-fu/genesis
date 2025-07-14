#include <stdlib.h>

#include "token.h"
#include "utility.h"
#include "generics.h"
#include "vector.h"
#include "assertf.h"

owned Token * tk_new() {
    owned Token * tk = new(sizeof(Token));
    tk->tt           = TOKEN_UNKNOWN;
    tk->value        = nil;
    return tk;
}

owned Token * tk_ctor(copy const TToken tt, borrowed const char * value) {
    owned Token * tk = tk_new();
    tk->tt           = tt;
    tk->value        = s_copy(value);
    return tk;
}

owned Token * tk_ctor_owned(copy const TToken tt, owned char * value) {
    owned Token * tk = tk_new();
    tk->tt           = tt;
    tk->value        = value;
    return tk;
}

owned TKs * tks_new() {
    return vec_new();
}

copy TToken tks_tt_own(borrowed TKs * tks) {
    scp(tks);
    cassert(!vec_is_empty(tks));
    owned Token * tk = vec_popfront(tks);
    copy  TToken  tt = tk->tt;
    tk_destroy(tk);
    return tt;
}

copy TToken tks_tt_borrow(borrowed TKs * tks) {
    scp(tks);
    cassert(!vec_is_empty(tks));
    borrowed Token * tk = vec_front(tks);
    return tk->tt;
}

owned char * tks_value_own(borrowed TKs * tks) {
    scp(tks);
    cassert(!vec_is_empty(tks));
    owned Token * tk    = vec_popfront(tks);
    owned char  * value = s_copy(tk->value);
    tk_destroy(tk);
    return value;
}

owned char * tks_value_borrow(borrowed TKs * tks) {
    scp(tks);
    cassert(!vec_is_empty(tks));
    borrowed Token * tk = vec_front(tks);
    return s_copy(tk->value);
}

void tks_next_own(borrowed TKs * tks, borrowed TToken * tt, borrowed char ** value) {
    scp(tks);
    cassert(!vec_is_empty(tks));
    owned Token * tk = vec_popfront(tks);
    if (tt) {
        deref(tt, TToken) = tk->tt;
    }
    if (value) {
        deref(value, char*) = s_copy(tk->value);
    }
    tk_destroy(tk);
}

void tks_next_borrow(borrowed TKs * tks, borrowed TToken * tt, borrowed char ** value) {
    scp(tks);
    cassert(!vec_is_empty(tks));
    borrowed Token * tk = vec_front(tks);
    if (tt) {
        deref(tt, TToken) = tk->tt;
    }
    if (value) {
        deref(value, char*) = s_copy(tk->value);
    }
}

void tk_dtor(borrowed void * arg) {
    if (eq(nil, arg)) {
        return;
    }
    borrowed Token * tk = cast(arg, Token*);

    tk->tt = TOKEN_UNKNOWN;
    sfree(tk->value);
}

void tk_destroy(owned void * arg) {
    if (eq(nil, arg)) {
        return;
    }
    tk_dtor(arg);
    free(arg);
}

void tks_dtor(borrowed void * arg) {
    if (!arg) {
        return;
    }
    borrowed TKs * tks = cast(arg, TKs*);
    vec_dtor(tks, tk_destroy);
}

void tks_destroy(borrowed void * arg) {
    if (!arg) {
        return;
    }
    tks_dtor(arg);
    free(arg);
}

