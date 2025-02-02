#include <stdio.h>
//#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

#define BILLION  1000000000L
#define MILLION  1000000L
#define THOUSAND 1000L

void get_time_ts(struct timespec *t0) {
	if (clock_gettime(CLOCK_REALTIME, t0) == -1) {
		perror("clock_gettime");
		exit(1);
	}
}

long long duration_ns(struct timespec t0, struct timespec t1) {
	return ((t1.tv_sec - t0.tv_sec)*BILLION) + (t1.tv_nsec - t0.tv_nsec);
}

void print_time_ns(long long time) {
	printf("%llds %lldms %lldµ %lldns\n"
		, time/BILLION
		, (time/MILLION)%THOUSAND
		, (time/THOUSAND)%THOUSAND
		, time%THOUSAND
	);
}

int main (int argc, char** argv) {
	struct timespec t0, t1;

	get_time_ts(&t0);

	int i = 0;
	while (i < 10000) { i++; }

	get_time_ts(&t1);

	long long time = duration_ns(t0, t1);

	print_time_ns(time);

	return 0;
}

/*  // For limited precision: timeval structure + gettimeofday function.
	struct timeval t0, t1;

	gettimeofday (&t0, NULL);
	int i = 0;
	while (i < 10000) { i++; }

	gettimeofday (&t1, NULL);

	printf("%ld ms\n", (t1.tv_sec - t0.tv_sec)*BILLION + (t1.tv_usec - t0.tv_usec));
*/
