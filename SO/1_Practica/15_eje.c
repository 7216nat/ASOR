#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <locale.h>

int main(){

	time_t t = time(NULL);
	struct tm *_tm = localtime(&t);
	
	char buf[100];
	printf("Locale es: %s\n", setlocale(LC_ALL, "es_ES.utf8"));
	strftime(buf, 100, "%A, %d de %B de %Y, %H:%M", _tm);
	printf("Hora es: %s\n", buf);
	return 0;
}
