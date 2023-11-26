#include "shared.h"
#include <time.h>
#include <stdio.h>

extern int parse(int, char **);
extern void report(char *, ullint, double);
extern ullint compute_with_processes();
extern ullint compute_with_threads();

ullint N;
int n;
ullint analytic_sum;

int main(int argc, char *argv[]) {
    ullint sum;
    clock_t start, end;

    if (parse(argc, argv)) {
        return -1;
    }

    printf("\n");

    start = clock();
    sum = analytic_sum = N * (N + 1) / 2;
    end = clock();
    report("analytic", sum, (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    sum = compute_with_processes();
    end = clock();
    report("processes", sum, (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    sum = compute_with_threads();
    end = clock();
    report("threads", sum, (double)(end - start) / CLOCKS_PER_SEC);

    printf("\n");

    return 0;
}
