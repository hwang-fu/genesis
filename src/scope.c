#include <stdlib.h>
#include <sys/syslimits.h>

#include "scope.h"
#include "token.h"
#include "assertf.h"
#include "generics.h"
#include "hashmap.h"
#include "variable.h"
#include "type.h"

static owned Scope * gs = nil;
static owned Scope * ls = nil;

static owned Scope * scope_new() {
    owned Scope * scope = new(sizeof(Scope));
    scope->tscope = map_new();
    scope->vscope = map_new();
    return scope;
}

void scope_init() {
    assert_eq(nil, gs);
    gs = scope_new();
}

void scope_fin() {
    scope_destroy(gs);
    gs = nil;
}

borrowed Scope * gscope() {
    return gs;
}

copy Bool gscope_v_exists(borrowed const char * vname) {
    scp(gs);
    scp(gs->vscope);
    scp(vname);
    return map_contains_key(gs->vscope, vname);
}

copy Bool gscope_v_exists_owned(owned char * vname) {
    copy Bool result = gscope_v_exists(vname);
    free(vname);
    return result;
}

copy Bool gscope_t_exists(borrowed TKs * tks, copy TToken tt, borrowed const char * tname) {
    scp(gs);
    scp(gs->tscope);
    scp(tname);
    if (eq(TOKEN_AT, tt)) {
        tt = tks_tt_borrow(tks);
        return gscope_t_exists_owned(tks, tt, tks_value_own(tks));
    }
    return map_contains_key(gs->tscope, tname);
}

copy Bool gscope_t_exists_owned(borrowed TKs * tks, copy TToken tt, owned char * tname) {
    copy Bool result = gscope_t_exists(tks, tt, tname);
    free(tname);
    return result;
}

copy Bool gscope_v_insert(borrowed const char * vname, owned Variable * gvar) {
    scp(gs);
    scp(gs->vscope);
    scp(vname);
    scp(gvar);
    if (gscope_v_exists(vname)) {
        return False;
    }
    map_insert_key(gs->vscope, vname, gvar);
    return True;
}

copy Bool gscope_v_insert_owned(owned char * vname, owned Variable * gvar) {
    copy Bool result = gscope_v_insert(vname, gvar);
    free(vname);
    return result;
}

copy Bool gscope_t_insert(borrowed const char * tname, owned Type * ty) {
    scp(gs);
    scp(gs->tscope);
    scp(tname);
    scp(ty);
    if (gscope_t_exists(nil, TOKEN_UNKNOWN, tname)) {
        return False;
    }
    map_insert_key(gs->tscope, tname, ty);
    return True;
}

copy Bool gscope_t_insert_owned(owned char * tname, owned Type * ty) {
    copy Bool result = gscope_t_insert(tname, ty);
    free(tname);
    return result;
}

borrowed Scope * lscope() {
    return ls;
}

borrowed Scope * lscope_enter() {
    if (ls) {
        error("Nested local scopes are not allowed by far.");
    }
    ls = scope_new();
    return ls;
}

void lscope_leave() {
    if (!ls) {
        error("Attempting to leave a local scope when none is active.");
    }
    scope_destroy(ls);
    ls = nil;
}

copy Bool lscope_v_exists(borrowed const char * vname) {
    scp(ls);
    scp(ls->vscope);
    scp(vname);
    return map_contains_key(ls->vscope, vname);
}

copy Bool lscope_v_exists_owned(owned char * vname) {
    copy Bool result = lscope_v_exists(vname);
    free(vname);
    return result;
}

copy Bool lscope_t_exists(borrowed TKs * tks, copy TToken tt, borrowed const char * tname) {
    scp(ls);
    scp(ls->tscope);
    scp(tname);
    if (eq(TOKEN_AT, tt)) {
        tt = tks_tt_borrow(tks);
        return lscope_t_exists_owned(tks, tt, tks_value_own(tks));
    }
    return map_contains_key(ls->tscope, tname);
}

copy Bool lscope_t_exists_owned(borrowed TKs * tks, copy TToken tt, owned char * tname) {
    copy Bool result = lscope_t_exists(tks, tt, tname);
    free(tname);
    return result;
}

copy Bool lscope_v_insert(borrowed const char * vname, owned Variable * lvar) {
    scp(ls);
    scp(ls->vscope);
    scp(vname);
    scp(lvar);
    if (lscope_v_exists(vname)) {
        return False;
    }
    map_insert_key(ls->vscope, vname, lvar);
    return True;
}

copy Bool lscope_v_insert_owned(owned char * vname, owned Variable * lvar) {
    copy Bool result = lscope_v_insert(vname, lvar);
    free(vname);
    return result;
}

copy Bool lscope_t_insert(borrowed const char * tname, owned Type * ty) {
    scp(ls);
    scp(ls->tscope);
    scp(tname);
    scp(ty);
    if (lscope_t_exists(nil, TOKEN_UNKNOWN, tname)) {
        return False;
    }
    map_insert_key(ls->tscope, tname, ty);
    return True;
}

copy Bool lscope_t_insert_owned(owned char * tname, owned Type * ty) {
    copy Bool result = lscope_t_insert(tname, ty);
    free(tname);
    return result;
}

void scope_dtor(borrowed void * arg) {
    if (!arg) {
        return;
    }
    borrowed Scope * sc = cast(arg, Scope*);
    map_destroy(sc->tscope, ty_destroy);
    map_destroy(sc->vscope, var_destroy);
    sc->tscope = nil;
    sc->vscope = nil;
}

void scope_destroy(owned void * arg) {
    if (!arg) {
        return;
    }
    scope_dtor(arg);
    free(arg);
}

