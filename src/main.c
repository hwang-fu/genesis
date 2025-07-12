#include <stdio.h>

#include "assertf.h"

int main(int argc, const char * argv[]) {

    logger_ctor();

    warning("ABC");

    logger_dtor();

    return 0;

}

