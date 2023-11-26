#include "shared.h"
#include <stdio.h>
#include <stdlib.h>

int parse(int argc, char *argv[]) {
    char *message = "usage: sum N n";

    if (argc != 3) {
        printf("%s\n", message);
        return -1;
    }

    N = strtoull(argv[1], NULL, 10);
    n = atoi(argv[2]);

    return 0;
}
