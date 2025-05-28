#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
    struct sched_param param;

    param.sched_priority = 1;
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler para proceso main");
        exit(EXIT_FAILURE);
    }

    while (1) { /* xd*/ }

    return 0;
}
