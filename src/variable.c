#include <stdlib.h>

#include "variable.h"
#include "generics.h"
#include "utility.h"

owned Variable * var_new() {
    owned Variable * var = new(sizeof(Variable));
    var->tag             = VAR_GLOBAL;
    var->name            = nil;
    var->type            = nil;
    var->offset          = 0;
    var->enumer          = 0;
    return var;
}

owned Variable * lvar_new() {
    owned Variable * var = new(sizeof(Variable));
    var->tag             = VAR_LOCAL;
    var->name            = nil;
    var->type            = nil;
    var->offset          = 0;
    var->enumer          = 0;
    return var;
}

owned Variable * lvar_ctor(borrowed const char * name, borrowed Type * type, copy i64 offset) {
    owned Variable * lvar = lvar_new();
    lvar->name            = s_copy(name);
    lvar->type            = type;
    lvar->offset          = offset;
    return lvar;
}

owned Variable * lvar_ctor_owned(owned char * name, borrowed Type * type, copy i64 offset) {
    owned Variable * lvar = lvar_new();
    lvar->name            = name;
    lvar->type            = type;
    lvar->offset          = offset;
    return lvar;
}

owned Variable * gvar_new() {
    owned Variable * var = new(sizeof(Variable));
    var->tag             = VAR_GLOBAL;
    var->name            = nil;
    var->type            = nil;
    var->offset          = 0;
    var->enumer          = 0;
    return var;
}

owned Variable * gvar_ctor(borrowed const char * name, borrowed Type * type) {
    owned Variable * gvar = gvar_new();
    gvar->name            = s_copy(name);
    gvar->type            = type;
    return gvar;
}

owned Variable * gvar_ctor_owned(owned char * name, borrowed Type * type) {
    owned Variable * gvar = gvar_new();
    gvar->name            = name;
    gvar->type            = type;
    return gvar;
}

void var_dtor(borrowed void * arg) {
    if (!arg) {
        return;
    }
    borrowed Variable * var = cast(arg, Variable*);
    sfree(var->name);
}

void var_destroy(owned void * arg) {
    if (!arg) {
        return;
    }
    var_dtor(arg);
    free(arg);
}

