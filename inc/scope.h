#ifndef GENESIS_SCOPE_H
#define GENESIS_SCOPE_H

#include "generics.h"
#include "hashmap.h"

typedef struct Scope Scope;
struct Scope {
    owned Map * tscope;
    owned Map * vscope;
};

void scope_init();
void scope_fin();

#endif // GENESIS_SCOPE_H
