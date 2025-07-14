#include <stdio.h>

#include "assertf.h"
#include "label.h"

void genesis_init();
void genesis_init() {
    logger_ctor();
    label_ctor();
}

void genesis_fin();
void genesis_fin() {
    logger_dtor();
    label_dtor();
}

int main(int argc, const char * argv[]) {

    genesis_init();

    genesis_fin();

    return 0;

}

