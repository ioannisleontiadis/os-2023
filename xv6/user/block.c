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
    case 2:
        printf(1, "my favorite number is %d\n", getfavnum());
        break;
    case 3:
        printf(1, "getfavnum was called %d times\n", getcount(23));
        printf(1, "calling getfavnum\n");
        getfavnum();
        printf(1, "getfavnum was called %d times\n", getcount(23));
        if (fork() == 0) {
            printf(1, "calling getfavnum from another process\n");
            getfavnum();
        } else {
            wait();
            printf(1, "getfavnum was called %d times\n", getcount(23));
        }
        break;
    default:
        printf(2, "not implemented\n");
    }

    exit();
}
