#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv){

    if (argc != 2) {
		 printf("usage: %s <command_string>.\n", argv[0]);
		 exit(EXIT_FAILURE);
	}

    if (system(argv[1]) < 0) {
        perror("system() error.\n");
        exit(EXIT_FAILURE);
    }

    printf("El comando terminó de ejecutarse.\n");
    return 0;
}