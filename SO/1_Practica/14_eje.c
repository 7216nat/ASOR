#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

int main(){

	time_t t = time(NULL);
	struct tm *_tm = localtime(&t);
	
	printf("Año: %d\n", 1900 + _tm->tm_year);
	return 0;
}
