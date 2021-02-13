#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {

    int fd;

	if (argc < 2) {
		 printf("usage: %s <ruta>.\n", argv[0]);
		 exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0666);
    if (fd < 0){
        perror("open() error.\n");
		exit(EXIT_FAILURE);
    }

    if (dup2(fd, 1) < 0){
        perror("dup2() error.\n");
        close(fd);
		exit(EXIT_FAILURE);
    }

    printf("Hola Mundo!\n");
    close(fd);
	return 0;
}