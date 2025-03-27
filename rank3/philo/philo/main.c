#include <sys/time.h>
#include <stdio.h>

int main() {
    struct timeval	current_time;
	long			seconds;
    long			microseconds;
    long			milliseconds;

    if (gettimeofday(&current_time, NULL) == -1) {
        printf("Error: gettimeofday");
        return 1;
    }
    seconds = current_time.tv_sec;
    microseconds = current_time.tv_usec;
    milliseconds = seconds * 1000 + microseconds / 1000;
    printf("Current timestamp in milliseconds: %ld\n", milliseconds);
    return 0;
}