#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>

int a2, b1, c1, c2, x, y, z;
sem_t *sem1, *sem2, *sem3, *sem4;

void *thread_t1(void *);
void *thread_t2(void *);
void *thread_t3(void *);

int main(int argc, char *argv[]) {
    pthread_t t1, t2, t3;

    sem1 = sem_open("/sem1", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
    sem2 = sem_open("/sem2", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
    sem3 = sem_open("/sem3", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
    sem4 = sem_open("/sem4", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);

    pthread_create(&t1, NULL, &thread_t1, NULL);
    pthread_create(&t2, NULL, &thread_t2, NULL);
    pthread_create(&t3, NULL, &thread_t3, NULL);

    pthread_join(t1, NULL);
    
    sem_unlink("/sem1");
    sem_unlink("/sem2");
    sem_unlink("/sem3");
    sem_unlink("/sem4");
    
    return 0;
}

int count = 0;

void *thread_t1(void *args) {
    int a1 = 10;
    printf("t1: a1 = %d\n", a1);

    a2 = 11;
    printf("t1: a2 = %d\n", a2);
    sem_post(sem1);

    sem_wait(sem2);
    y = a1 + c1;
    printf("t1: y = a1(%d) + c1(%d) = %d\n", a1, c1, y);
    sem_post(sem3);
    
    sem_wait(sem4);
    printf("x = %d\n", x);

    pthread_exit(NULL);
}

void *thread_t2(void *args) {
    b1 = 20;
    printf("t2: b1 = %d\n", b1);
    sem_post(sem1);

    int b2 = 21;
    printf("t2: b2 = %d\n", b2);

    sem_wait(sem2);
    sem_wait(sem2);
    int w = b2 + c2;
    printf("t2: w = b2(%d) + c2(%d) = %d\n", b2, c2, w);

    sem_wait(sem3);
    sem_wait(sem3);
    x = z - y + w;
    printf("t2: x = z(%d) - y(%d) + w(%d) = %d\n", z, y, w, x);
    sem_post(sem4);

    pthread_exit(NULL);
}

void *thread_t3(void *args) {
    c1 = 30;
    printf("t3: c1 = %d\n", c1);
    sem_post(sem2);

    c2 = 31;
    printf("t3: c2 = %d\n", c2);
    sem_post(sem2);
    sem_post(sem2);

    sem_wait(sem1);
    sem_wait(sem1);
    z = a2 + b1;
    printf("t3: z = a2(%d) + b1(%d) = %d\n", a2, b1, z);
    sem_post(sem3);

    pthread_exit(NULL);
}
