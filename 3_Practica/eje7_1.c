#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv){

    if (argc < 2) {
		 printf("usage: %s <command>.\n", argv[0]);
		 exit(EXIT_FAILURE);
	}

    if (execvp(argv[1], argv + 1) < 0) {
        perror("execvp() error.\n");
        exit(EXIT_FAILURE);
    }

    printf("El comando terminó de ejecutarse.\n");
    return 0;
}