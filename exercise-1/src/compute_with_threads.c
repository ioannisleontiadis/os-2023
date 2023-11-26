#include "shared.h"
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int idx;
    ullint psum;
} thread_data;

ullint change;
thread_data *data;

void *thread(void *args);

ullint compute_with_threads() {
    change = N / n;
    pthread_t ids[n];
    data = (thread_data *)malloc(sizeof(thread_data) * n);

    for (int i = 0; i < n; i++) {
        data[i].idx = i;
        pthread_create(&ids[i], NULL, thread, (void *)(&data[i].idx));
    }

    for (int i = 0; i < n; i++) {
        pthread_join(ids[i], NULL);
    }

    ullint sum = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i].psum;
    }

    return sum;
}

void *thread(void *arg) {
    int idx = *((int *)arg);
    ullint start = 1 + idx * change;
    ullint end = idx < n - 1 ? (idx + 1) * change : N;

    ullint psum = 0;
    for (ullint num = start; num <= end; num++) {
        psum += num;
    }
    data[idx].psum = psum;

    pthread_exit(NULL);
}
