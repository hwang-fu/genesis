#include <stdio.h>

#include "assertf.h"
#include "label.h"
#include "scope.h"

void genesis_init();
void genesis_init() {
    logger_init();
    label_init();
    scope_init();
}

void genesis_fin();
void genesis_fin() {
    logger_fin();
    label_fin();
    scope_fin();
}

int main(int argc, const char * argv[]) {

    genesis_init();

    genesis_fin();

    return 0;

}

