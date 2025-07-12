#ifndef GENESIS_LEX_H
#define GENESIS_LEX_H

#include "token.h"
#include "generics.h"

owned TKs * scan(owned char * content);
owned TKs * lex(borrowed const char * filename);

#endif // GENESIS_LEX_H
