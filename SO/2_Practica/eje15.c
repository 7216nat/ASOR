#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <locale.h>

int main(int argc, char **argv) {

    int fd;
    char buf[100];

	if (argc < 2) {
		 printf("usage: %s <ruta>.\n", argv[0]);
		 exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0){
        perror("open() error.\n");
		exit(EXIT_FAILURE);
    }

    if (lockf(fd, F_TLOCK, 0) < 0){
        perror("fichero bloqueado error.\n");
        close(fd);
		exit(EXIT_FAILURE);
    }

    printf("lock cogido y bloqueado.\n");
	setlocale(LC_ALL, "es_ES.utf8");
	time_t t = time(NULL);
	struct tm *tm= localtime(&t);
    strftime(buf, 100, "%A, %d de %B de %Y, %H:%M\n", tm);
	write(fd, buf, strlen(buf));
    sleep(30);
    lockf(fd, F_ULOCK, 0);
    printf("lock desbloqueado.\n");
    close(fd);
    
	return 0;
}