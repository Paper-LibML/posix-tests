#define _GNU_SOURCE
#include <sched.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void print_scheduler_info(const char* context_msg) {
	int policy = sched_getscheduler(0);
	struct sched_param param;
	sched_getparam(0, &param);

	const char* policy_str;

	switch (policy) {
		case SCHED_OTHER: policy_str = "SCHED_OTHER"; break;
		case SCHED_FIFO: policy_str = "SCHED_FIFO"; break;
		case SCHED_RR: policy_str = "SCHED_RR"; break;
		case SCHED_BATCH: policy_str = "SCHED_BATCH"; break;
		case SCHED_IDLE: policy_str = "SCHED_IDLE"; break;
		default: policy_str = "Unknown"; break;
	}

	printf("[%s] PID %d: Policy: %s, Priority: %d\n",
			context_msg, getpid(), policy_str, param.sched_priority);
}

int main(int argc, char** argv) {
	unsigned long long a = 0;
	unsigned long long limit = 18446744073709551615ULL;
	unsigned long long user_limit = strtoull(argv[1], NULL, 10);

	print_scheduler_info("initial");

	struct sched_param param;
	int prio = 0;
	prio = sched_get_priority_max(SCHED_RR);
	prio = sched_get_priority_min(SCHED_RR);

	param.sched_priority = 1;

	sched_setscheduler(0, SCHED_RR, &param);
	sched_setparam(0, &param);

	print_scheduler_info("after setting");

	if (user_limit < limit) {
		limit = user_limit;
	}

	while (a < limit) {
		a += 1;
	}

	printf("Counted to %llu\n", limit);
}
