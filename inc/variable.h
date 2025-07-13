#ifndef GENESIS_VARIABLE_H
#define GENESIS_VARIABLE_H

#include "generics.h"
#include "type.h"

typedef enum TVariable TVariable;
enum TVariable {
    VAR_LOCAL,
    VAR_GLOBAL,
    VAR_ENUMER,
};

typedef struct Variable Variable;
struct Variable {
    copy     TVariable tag;
    owned    char *    name;
    borrowed Type *    type;
    copy     i64       offset;
    copy     u64       enumer;
};
typedef Variable Parameter;

owned Variable * var_new();
owned Variable * lvar_new();
owned Variable * lvar_ctor(borrowed const char * name, borrowed Type * type, copy i64 offset);
owned Variable * lvar_ctor_owned(owned char * name, borrowed Type * type, copy i64 offset);
owned Variable * gvar_new();
owned Variable * gvar_ctor(borrowed const char * name, borrowed Type * type);
owned Variable * gvar_ctor_owned(owned char * name, borrowed Type * type);

void var_dtor(borrowed void * arg);
void var_destroy(owned void * arg);

#endif // GENESIS_VARIABLE_H
