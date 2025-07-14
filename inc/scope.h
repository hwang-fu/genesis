#ifndef GENESIS_SCOPE_H
#define GENESIS_SCOPE_H

#include "generics.h"
#include "hashmap.h"
#include "token.h"
#include "variable.h"
#include "type.h"

typedef struct Scope Scope;
struct Scope {
    owned Map * tscope;
    owned Map * vscope;
};

void scope_init();
void scope_fin();

borrowed Scope * gscope();
copy Bool gscope_v_exists(borrowed const char * vname);
copy Bool gscope_v_exists_owned(owned char * vname);
copy Bool gscope_t_exists(borrowed TKs * tks, copy TToken tt, borrowed const char * tname);
copy Bool gscope_t_exists_owned(borrowed TKs * tks, copy TToken tt, owned char * tname);
copy Bool gscope_v_insert(borrowed const char * vname, owned Variable * gvar);
copy Bool gscope_v_insert_owned(owned char * vname, owned Variable * gvar);
copy Bool gscope_t_insert(borrowed const char * tname, owned Type * ty);
copy Bool gscope_t_insert_owned(owned char * tname, owned Type * ty);

borrowed Scope * lscope();
borrowed Scope * lscope_enter();
void lscope_leave();
copy Bool lscope_v_exists(borrowed const char * vname);
copy Bool lscope_v_exists_owned(owned char * vname);
copy Bool lscope_t_exists(borrowed TKs * tks, copy TToken tt, borrowed const char * tname);
copy Bool lscope_t_exists_owned(borrowed TKs * tks, copy TToken tt, owned char * tname);
copy Bool lscope_v_insert(borrowed const char * vname, owned Variable * lvar);
copy Bool lscope_v_insert_owned(owned char * vname, owned Variable * lvar);
copy Bool lscope_t_insert(borrowed const char * tname, owned Type * ty);
copy Bool lscope_t_insert_owned(owned char * tname, owned Type * ty);

void scope_dtor(borrowed void * arg);
void scope_destroy(owned void * arg);

#endif // GENESIS_SCOPE_H
