#include "shared.h"
#include <stdio.h>

void report(char *name, ullint sum, double duration) {

    if (analytic_sum == sum) {
        printf("%s:\t1+2+..+%llu = %llu (%.4fs)\n", name, N, sum, duration);
    } else {
        printf("%s:\t1+2+..+%llu = %llu ≠ %llu (%.4fs)\n", name, N,
               analytic_sum, sum, duration);
    }
}
