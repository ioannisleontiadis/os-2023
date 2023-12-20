#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

#define N 6

void *thread(void *args);

int main(int argc, char *argv[]) {
	pthread_t threads[N];
	
	printf("Main thread pid = %d\n", getpid());
	sleep(15);

	for(int i = 0; i < N; i++) {
		sleep(10);
		pthread_create(&threads[i], NULL, thread, NULL);
	}

	for(int i = 0; i < N; i++) {
		pthread_join(threads[i], NULL);
	}

	return 0;
}

void *thread(void *args) {
	printf("Thread tid = %d\n", syscall(SYS_gettid));
	for(;;);
}
