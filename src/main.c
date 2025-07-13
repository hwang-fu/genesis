#include <stdio.h>

#include "assertf.h"

void genesis_init();
void genesis_init() {
    logger_ctor();
}

void genesis_fin();
void genesis_fin() {
    logger_dtor();
}

int main(int argc, const char * argv[]) {

    genesis_init();

    genesis_fin();

    return 0;

}

