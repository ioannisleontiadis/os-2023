#include "shared.h"
#include <stdlib.h>
#include <unistd.h>

void fork_children();
ullint compute(ullint start, ullint end);

int fd[2];

ullint compute_with_processes() {
    ullint sum = 0;
    ullint psum = 0;
    pipe(fd);

    fork_children();
    close(fd[1]);

    while (read(fd[0], &psum, sizeof(ullint)) > 0) {
        sum += psum;
    }

    close(fd[0]);
    while (wait(NULL) > 0)
        ;

    return sum;
}

void fork_children() {
    ullint change = N / n;

    for (int i = 0; i < n; i++) {
        if (!fork()) {
            ullint psum = 0;
            close(fd[0]);

            psum = i < n - 1 ? compute(1 + i * change, (i + 1) * change)
                             : compute(1 + i * change, N);

            write(fd[1], &psum, sizeof(ullint));
            close(fd[1]);
            _exit(EXIT_SUCCESS);
        }
    }
}

ullint compute(ullint start, ullint end) {
    ullint psum = 0;
    for (ullint num = start; num <= end; num++) {
        psum += num;
    }
    return psum;
}
