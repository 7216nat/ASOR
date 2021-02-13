#include <time.h>
#include <errno.h>
#include <stdio.h>

int main() {
	time_t t = time(NULL);
	
	if (t < 0){
		perror("time() error");
		return -1;
	}
	else
		printf("Seconds since 1/1/1970 00:00:00 UTC: %ld\n", t);
	return 0;
}
