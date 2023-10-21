#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int id, pid, killed;

    if (argc < 2) {
        printf(2, "usage: block id argument1, argument2, ..\n");
        exit();
    }

    id = atoi(argv[1]);

    switch (id) {
    case 1:
        pid = atoi(argv[2]);
        killed = kill(pid);
        if (killed == 0) {
            printf(1, "process %d killed\n", pid);
        } else {
            printf(1, "process %d could not be killed\n", pid);
        }
        break;
    default:
        printf(2, "not implemented\n");
    }

    exit();
}
