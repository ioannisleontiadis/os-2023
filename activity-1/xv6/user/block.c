#include "types.h"
#include "user.h"
#define DELAY 300
#define CALLING "☎️ "
#define KILLING "☠️ "
#define EXITING "✨"

void dots() {
    for (int i = 0; i < 2; i++) {
        sleep(DELAY / 4);
        printf(1, ".");
    }
    sleep(DELAY / 3);
}

void dashes(int n) {
    char d[50];
    for (int i = 0; i < n; i++) {
        d[i] = '-';
    }
    printf(1, "%s", d);
}

void heading(int n, char *s) {
    printf(1, "\n");
    printf(1, "Block %d: %s\n", n, s);
    dashes(40);
    printf(1, "\n\n");
}

void block1() {
    heading(1, "My favorite number");
    printf(1, "my favorite number is");
    dots();
    printf(1, " %d%s\n\n", getfavnum(), EXITING);
}

void block2() {
    heading(2, "Count system calls");
    printf(1, "previously getfavnum was called %d times\n\n", getcount(23));
    printf(1, "%s calling getfavnum", CALLING);
    getfavnum();
    dots();
    printf(1, "\ngetfavnum was called %d times\n\n", getcount(23));
    if (fork() == 0) {
        printf(1, "%s calling getfavnum from another process", CALLING);
        getfavnum();
        dots();
    } else {
        wait();
        printf(1, "\ngetfavnum was called %d times\n\n", getcount(23));
    }
}

void block3(int n) {
    heading(3, "Randomly killing processes");

    for (int i = 0; i < n; i++) {
        printf(1, "\33[2K\r");
        printf(1, "creating child processes %d\\%d", i + 1, n);
        sleep(DELAY / 16);
        if (fork() == 0) {
            for (;;) {
            }
        }
    }
    printf(1, "\n\nstarting to kill them randomly\n");
    for (int i = 0; i < n; i++) {
        sleep(DELAY / 8);
        int pid = killrandom();
        if (pid != -1) {
            printf(1, "%s killed process %d\n", KILLING, pid);
        } else {
            printf(1, "no processes to kill\n");
        }
        wait();
    }
    printf(1, "\n");
}

int main(int argc, char *argv[]) {
    int id;

    if (argc < 2) {
        printf(2, "usage: block id args\n");
        exit();
    }

    id = atoi(argv[1]);

    switch (id) {
    case 1:
        block1(argv[2]);
        break;
    case 2:
        block2();
        break;
    case 3:
        block3(atoi(argv[2]));
        break;
    default:
        printf(2, "not implemented\n");
    }

    exit();
}
