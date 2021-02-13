#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <sys/time.h>

int main(){
 	struct timeval tv;
	if (gettimeofday(&tv, NULL) < 0){
  		perror("gettimeofday() error");
  		return -1;
  	}
 	int start = tv.tv_usec;
 	
	for (int i = 0; i < 1000000; i++);
	
  	if (gettimeofday(&tv, NULL) < 0){
  		perror("gettimeofday() error");
  		return -1;
  	}
  	int end = tv.tv_usec;

	printf("El tiempo tardado (ms): %d\n", end - start);

	return 0;
}
