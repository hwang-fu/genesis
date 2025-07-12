#include <stdlib.h>

#include "token.h"
#include "utility.h"
#include "generics.h"
#include "vector.h"

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

