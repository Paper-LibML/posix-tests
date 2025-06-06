#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 4

void* thread_func(void* arg) {
    int id = *(int*)arg;
    printf("Thread %d running with RT priority\n", id);
    while(1) {
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    pthread_attr_t attr;
    struct sched_param param;
    int ids[N];
    int common_prio = 1;  // rt_priority for common threads

    struct sched_param main_param;

    // Set rt_priority for main process
    main_param.sched_priority = 1;
    if (sched_setscheduler(0, SCHED_FIFO, &main_param) == -1) {
        perror("sched_setscheduler - main process");
        exit(EXIT_FAILURE);
    }
    printf("Main process with rt_priority = %d\n", main_param.sched_priority);

    for (int i = 0; i < N; i++) {
        pthread_attr_init(&attr);

        pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
        pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

        param.sched_priority = common_prio;
        pthread_attr_setschedparam(&attr, &param);

        ids[i] = i;
        if (pthread_create(&threads[i], &attr, thread_func, &ids[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }

        pthread_attr_destroy(&attr);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
