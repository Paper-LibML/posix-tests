#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long x = 0;

int main() {
    struct sched_param param;

    param.sched_priority = 1;
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler - main");
        exit(EXIT_FAILURE);
    }

    while (1) { x++; }

    return 0;
}
