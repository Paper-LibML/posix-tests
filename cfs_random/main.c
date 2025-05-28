#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/prctl.h>
#include <unistd.h>

#define NUM_THREADS 5

typedef struct
{
    int pid, tid;
    long counter;
} ThreadData;

void *increment_forever(void *arg)
{
    ThreadData *data = (ThreadData*)arg;
    data->counter = 0;

    char name[16];
    snprintf(name, sizeof(name), "pid_%d_tid_%d", data->pid, data->tid);
    prctl(PR_SET_NAME, name);

    while (1) data->counter++;

    return NULL;
}

int main()
{
    int pid = fork();
    pthread_t threads[NUM_THREADS];
    ThreadData data[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i)
    {
	data[i].tid = i;
	data[i].pid = pid;
    	pthread_create(&threads[i], NULL, increment_forever, &data[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i)
        pthread_join(threads[i], NULL);

    return 0;
}
