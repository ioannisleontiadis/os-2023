#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

#define FORK_TIME 8
#define MAX_CHILDREN 10
#define SLEEP_TIME 1000

int children[MAX_CHILDREN];

int main(int argc, char *argv[]) {
	printf("pid = %d\n", getpid());

	for (int i = 0; i < MAX_CHILDREN; i++) {
		children[i] = fork();

		if (children[i]) {
			sleep(FORK_TIME);
			printf("Forked pid = %d\n", children[i]);
		} else {
			sleep(SLEEP_TIME);
			_exit(EXIT_SUCCESS);
		}
	}

	sleep(SLEEP_TIME);

	for (int i = 0; i < MAX_CHILDREN; i++) {
		kill(children[i], SIGTERM);
		wait(NULL);
	}

	return 0;
}
